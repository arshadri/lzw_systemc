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
// Description: Serial port model for verification purposes 
//
//*****************************************************************************   
#include "ser_model.h" 
  
  //assign rcv_byte = byte_in[7:0];
  void ser_model::process_rcv_byte ()
  {
   sc_biguint <9> byte_in_int;
   byte_in_int = byte_in;
   //rcv_byte = byte_in_int(7,0);
   rcv_byte.write((byte_in.read()[7],byte_in.read()[6],byte_in.read()[5],byte_in.read()[4],byte_in.read()[3],byte_in.read()[2],byte_in.read()[1],byte_in.read()[0]));
   //cout << "\tSER_MODEL: Received Byte = " << rcv_byte.read() << endl;
    
  }
  
  
  void ser_model::process_thread_initial ()
  {
    if (rst.read()) {
    cnt_cmd_bytes = 0x00;
    }
  }
  
  /****************************************************************************
    Transmit logic
  ****************************************************************************/    
  // Counter for counting 16 clocks, and than generates a terminal count.
  // On terminal count a new bit is transmitted out.
  void ser_model::process_clk1 ()
  {
    if (rst.read())
      xmt_cnt16.write(0x0);
    else if (!start_xmt.read())
      xmt_cnt16.write(0x0);
    else if (start_xmt.read())
      xmt_cnt16.write(xmt_cnt16 + 1);
  }
  
  //assign tc_xmt_cnt16 = xmt_cnt16 == 0xf;
  void ser_model::process_tc_xmt_cnt16 ()
  {
    tc_xmt_cnt16 = (xmt_cnt16 == 0xf);
  }
  
  // Transmit bit counter - transmit 8 data bits and one stop and start bit
  void ser_model::process_clk2 ()
  {
    if (rst.read())
      xmt_cnt.write(0x0);
    else if (!start_xmt.read())
      xmt_cnt.write(0x0);
    else if (start_xmt.read() & tc_xmt_cnt16.read())
      xmt_cnt.write(xmt_cnt + 1);
  }
  
  //assign tc_xmt_cnt = xmt_cnt == 0xa;
  void ser_model::process_tc_xmt_cnt ()
  {
    tc_xmt_cnt = (xmt_cnt == 0xa);
  }
  
  // Transmit serial register.
  void ser_model::process_clk3 ()
  {
    if (rst.read()) {
      bout.write(0x001);
      //ld_data.write(0);
    }
    else if (!start_xmt.read() | (start_xmt.read() & tc_xmt_cnt16.read() & (xmt_cnt.read() == 0x9)))
      bout.write(0x001);
    else if (ld_data.read())
    {
      bout.write((1,byte_out.read(),0));
      //ld_data.write(0);
    }
    else if (start_xmt.read() & tc_xmt_cnt16.read())
      bout.write(bout >> 1);
  }
  
  // Serial data out
  void ser_model::process_bout ()
  {
    sc_uint <10> bout_int;
    bout_int = bout.read();
    sout = bout_int[0];
  }

  /****************************************************************************
    Receive logic
  ****************************************************************************/   
  // Detect a valid start bit and start latching data into receive register.
  // If serial in is sampled low for 16 clocks than it is considered a valid
  // start bit.
  void ser_model::process_clk4 ()
  {
    if (rst.read())
      cnt.write(0xf);
    else if (sin.read() | tc.read() | valid_start.read())
      cnt.write(0xf);
    else if (!sin.read())
      cnt.write(cnt - 1);
  }
  
  void ser_model::process_tc ()
  {
    tc = (cnt.read() == 0x0);
  }
  
  // Generate valid start bit detected signal
  void ser_model::process_valid_start ()
  {
    if (rst.read())
      valid_start.write(0);
    else if (tc_rcv_cnt.read())
      valid_start.write(0);
    else if (tc.read())
      valid_start.write(1);
  }
  
  // Counter for counting 16 clocks, and than generates a terminal count.
  // On terminal count a new receive bit is loaded into the receive shift
  // register.
  void ser_model::process_clk5 ()
  {
    if (rst.read())
      rcv_cnt16.write(0x0);
    else if (!valid_start.read())
      rcv_cnt16.write(0x0);
    else if (valid_start.read())
      rcv_cnt16.write(rcv_cnt16 + 1);
  }
  
  void ser_model::process_tc_rcv_cnt16 ()
  {
    tc_rcv_cnt16 = (rcv_cnt16.read() == 0xf);
  }
    
  // Receive counter - 8 data bits and one stop and start bit
  void ser_model::process_clk6 ()
  {
    if (rst.read())
      rcv_cnt.write(0x0);
    else if (!valid_start.read())
      rcv_cnt.write(0x0);
    else if (valid_start.read() & tc_rcv_cnt16.read())
      rcv_cnt.write(rcv_cnt + 1);
  }
  
  void ser_model::process_tc_rcv_cnt ()
  {
    tc_rcv_cnt = (rcv_cnt == 0x9);
  }
  
  void ser_model::process_byte_in_int ()
  {
    sc_biguint <9> byte_in_int1;
    
    byte_in_int1 = byte_in;
    byte_in_int2 = byte_in_int1(8,1);
  }
    
  // Receive data shift register
  void ser_model::process_clk7 ()
  {
    if (rst.read())
      byte_in.write(0x00);
    else if (valid_start.read() & tc_rcv_cnt16.read())
       byte_in.write((sin.read(),byte_in.read()[8],byte_in.read()[7],byte_in.read()[6],byte_in.read()[5],byte_in.read()[4],byte_in.read()[3],byte_in.read()[2],byte_in.read()[1]));
  }
  
  // Display on Terminal the received data 
  void ser_model::process_clk8 ()
  {
    if (rst.read())
      disp_cnt.write(0);
    else if (tc_rcv_cnt.read())
    {
      disp_cnt.write(disp_cnt.read() + 1);
      cout << "\tSER_MODEL: Received Byte = , Byte Count = " << rcv_byte.read() << disp_cnt.read() << endl;
    }
  }
   
  /****************************************************************************
     Task to read from the receive register. This is data that has been
     received on serial in.
  ****************************************************************************/   
 
  void ser_model::process_read ()
  {
  sc_biguint <9> dout_int;
  dout_int = byte_in.read();
  
    dout.write(dout_int(7,0));
  }
  
  