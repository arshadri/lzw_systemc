//*****************************************************************************
// www.orahyn.com
// Copyright [2013] Orahyn (Pvt) Ltd.
// Licensed under the Apache License, Version 2.0 (the "License"); you may not 
// use this file except in compliance with the License. You may obtain a copy 
// of the License at http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software 
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT 
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the 
// License for the specific language governing permissions and limitations 
// under the License.

// Date:      01/07/13
// Description: Serial port (UART) implementation 
//
//*****************************************************************************
    #include "ser.h" 
 
  void ser::ser_combop () {
  	sc_uint<10 > bout_bits;
  	bout_bits = sc_uint<10>(bout);
       	sc_uint<9 > lbit;
       	sc_uint<8 > rbit;
        lbit = sc_uint<9>(byte_in);
        
      bout0.write(bout_bits[0]);
     sclk.write(sclk_cntr.read() == 17);
     tc_xmt_cnt16.write(xmt_cnt16.read() == 0xf);
     tc_xmt_cnt.write(xmt_cnt.read() == 0xa);       
     xmt_done.write(tc_xmt_cnt.read());
     ld_data.write(xmt_done_s.read() & !xmt_done_ss.read());  
     sout.write(bout0); // Serial data out  
     tc.write(cnt.read() == 0);
     tc_rcv_cnt16.write(rcv_cnt16.read() == 0xf);    
     tc_rcv_cnt.write(rcv_cnt.read() == 9);
     rcv_done.write(!rcv_done_s.read() & rcv_done_ss.read());
     rbit = (lbit[8],lbit[7],lbit[6],lbit[5],lbit[4],lbit[3],lbit[2],lbit[1]);
  }

  /****************************************************************************
    Divide clk in by 18 to get the sclk at the desired rate
    16*Baud rate. Baud rate is fixed at 115,200 bps
  ****************************************************************************/  
  void ser::sclk_cntrp () {
    if (!rst_n.read())
      sclk_cntr.write(0);
    else if (sclk_cntr.read() == 17)
      sclk_cntr.write(0);
    else 
      sclk_cntr.write(sclk_cntr.read() + 1);
  }
    
  /****************************************************************************
    Transmit logic
  ****************************************************************************/    
  // Counter for counting 16 clocks, and than generates a terminal count.
  // On terminal count a new bit is transmitted out.
  void ser::xmt_cnt16p () {
    if (!rst_n.read())
      xmt_cnt16.write(0);
    else if (!start_xmt.read() & sclk.read())
      xmt_cnt16.write(0);
    else if (start_xmt.read() & sclk.read())
      xmt_cnt16.write(xmt_cnt16.read() + 1);
  }
  
  // Transmit bit counter - transmit 8 data bits and one stop and start bit
  void ser::xmt_cntp () {
    if (!rst_n.read())
      xmt_cnt.write(0);
    else if (!start_xmt.read() & sclk.read())
      xmt_cnt.write(0);
    else if (start_xmt.read() & tc_xmt_cnt16.read() & sclk.read())
      xmt_cnt.write(xmt_cnt.read() + 1);
  }
  
  // Generate a pulse for the receive done signal
  void ser::xmt_donesp () {
    if (!rst_n.read()) {
      xmt_done_s.write(0);
      xmt_done_ss.write(0);
    }
    else {
      xmt_done_s.write(start_xmt.read());
      xmt_done_ss.write(xmt_done_s.read());
    }
  }
  
  // Transmit serial register.
  void ser::boutp () {
    if (!rst_n.read())
      bout.write(0x001);
    else if (ld_data.read())
      bout.write((1,xmt_byte.read(),0));
    else if (!start_xmt.read() | (start_xmt.read() & tc_xmt_cnt16.read() & xmt_cnt.read() == 9) & sclk.read())
      bout.write(0x001);
    else if (start_xmt.read() & tc_xmt_cnt16.read() & sclk.read())
      bout.write(bout.read() >> 1);
  }
 
  /****************************************************************************
    Receive logic
  ****************************************************************************/   
  // Detect a valid start bit and start latching data into receive register.
  // If serial in is sampled low for 16 clocks than it is considered a valid
  // start bit.
  void ser::cntp () {
    if (!rst_n.read())
      cnt.write(0xf);
    else if ((sin.read() | tc.read() | valid_start.read()) & sclk.read())
      cnt.write(0xf);
    else if (!sin.read()  & sclk.read())
      cnt.write(cnt.read() - 1);
  }
  
  // Generate valid start bit detected signal
  void ser::valid_startp () {
    if (!rst_n.read())
      valid_start.write(0);
    else if (tc_rcv_cnt.read())
      valid_start.write(0);
    else if (tc.read())
      valid_start.write(1);
  }
  
  // First valid start detection latched. For debug purposes on FPGA board,
  // will indicate serial port is communicating by lighting an LED on the 
  // board
  void ser::vld_str_debp () {
    if (!rst_n.read())
      vld_str_deb.write(0);
    else if (valid_start.read())
      vld_str_deb.write(1);
  }
 
  // Counter for counting 16 clocks, and than generates a terminal count.
  // On terminal count a new receive bit is loaded into the receive shift
  // register.
  void ser::rcv_cnt16p () {
    if (!rst_n.read())
      rcv_cnt16.write(0);
    else if (~valid_start.read() & sclk.read())
      rcv_cnt16.write(0);
    else if (valid_start.read() & sclk.read()){
      rcv_cnt16.write(rcv_cnt16.read() + 1);
      cout << "At time " << sc_time_stamp() << "::";
      cout << "\tSER:rcv_cnt16 " << rcv_cnt16  << endl;
    }
  }

  // Receive counter - 8 data bits and one stop and start bit
  void ser::rcv_cntp () {
    if (!rst_n.read())
      rcv_cnt.write(0);
    else if (~valid_start.read() & sclk.read())
      rcv_cnt.write(0);
    else if (valid_start.read() & tc_rcv_cnt16.read () & sclk.read()){
      rcv_cnt.write(rcv_cnt.read() + 1);
      cout << "At time " << sc_time_stamp() << "::";
      cout << "\tSER:rcv_cnt " << rcv_cnt  << endl;
    }
  }
  
  // Generate a pulse for the receive done signal
  void ser::rcv_done_sp () {
    if (!rst_n.read()) {
      rcv_done_s.write(0);
      rcv_done_ss.write(0);
    }
    else {
      rcv_done_s.write(tc_rcv_cnt.read());
      rcv_done_ss.write(rcv_done_s.read());
    }
  }

  // Receive data shift register
  void ser::byte_inp () {

    if (!rst_n.read())
      byte_in.write(0);
    else if (valid_start.read() & tc_rcv_cnt16.read () & sclk.read()){
      byte_in.write((sin.read(),byte_in.read()[8],byte_in.read()[7],byte_in.read()[6],byte_in.read()[5],byte_in.read()[4],byte_in.read()[3],byte_in.read()[2],byte_in.read()[1]));
      cout << "At time " << sc_time_stamp() << "::";
      cout << "\tSER:byte_in " << byte_in  << endl;
    }
  }
  
  // Receive data byte
  void ser::rcv_bytep () {
    if (!rst_n.read())
      rcv_byte.write(0);
    else if (tc_rcv_cnt.read () & sclk.read()) {
      rcv_byte.write((byte_in.read()[7],byte_in.read()[6],byte_in.read()[5],byte_in.read()[4],byte_in.read()[3],byte_in.read()[2],byte_in.read()[1],byte_in.read()[0]));
    
      cout << "At time " << sc_time_stamp() << "::";
      cout << "\tSER:rcv_byte " << rcv_byte << endl;
    }
  }
