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
    #include "systemc.h" 
  /****************************************************************************
    By default runs at 9600 Baud rate
  ****************************************************************************/
  SC_MODULE(ser) {
  // Outputs
       sc_out <sc_biguint<8> >  rcv_byte;      // Received data byte
       sc_out <bool >           sout;          // Serial data out
       sc_out <bool >           rcv_done;      // Reception of byte complete
       sc_out <bool >           xmt_done;      // Transmission of byte complete
       sc_out <bool >           vld_str_deb;   // Valid start on Rx detected for debug
  // Inputs
       sc_in <sc_biguint<8> >   xmt_byte;      // Byte to be transmitted
       sc_in <bool >            sin;           // Serial data in 
       sc_in <bool >            start_xmt;     // Start transmission of serial data
       sc_in <bool >            clk;          // From iopads
       sc_in <bool >            rst_n;        // From iopads


  /****************************************************************************
   Internal declarations
  ****************************************************************************/  
  sc_signal <sc_biguint<10> > bout;         // Byte to be transmitted with one start and stop bit
  sc_signal <sc_biguint<9> > byte_in;       // Byte received 
  sc_signal <sc_biguint<4> > xmt_cnt;       // Transmit bit count
  sc_signal <sc_biguint<4> > xmt_cnt16;     // Counter for holding the transmit data bit for 16 clock cycles
  sc_signal <sc_biguint<4> > cnt;           // Counter for detecting valid start bit
  sc_signal <sc_biguint<4> > rcv_cnt;       // Received bit count
  sc_signal <sc_biguint<4> > rcv_cnt16;     // Receive data bit is counted for 16 clocks for valid reception
  sc_signal <sc_biguint<8> > sclk_cntr;     // Counter for generating the desired baud rate clk
  sc_signal <bool >          valid_start;   // Valid start bit detected on received data
  sc_signal <bool >          rcv_done_s;    // Reception of byte complete, synch 1
  sc_signal <bool >          rcv_done_ss;   // Reception of byte complete, synch 2
  sc_signal <bool >          xmt_done_s;    // Transmission of byte complete, synch 1
  sc_signal <bool >          xmt_done_ss;   // Transmission of byte complete, synch 2
  sc_signal <bool >          tc;            // Terminal count
  sc_signal <bool >          tc_xmt_cnt;    // Terminal count for transmit bit counter
  sc_signal <bool >          tc_xmt_cnt16;  // Terminal count for holding the transmit bit for 16 clocks
  sc_signal <bool >          tc_rcv_cnt;    // Terminal count for receive bit counter
  sc_signal <bool >          tc_rcv_cnt16;  // Terminal count for holding the receive bit for 16 clocks
  sc_signal <bool >          sclk;          // Serial clock at 16 times the baud rate
  sc_signal <bool >          ld_data;       // Load data into transmit shift register
  sc_signal <bool >          bout0;
  sc_signal <sc_biguint<8> > rbit;
  
 
   SC_CTOR(ser) {
   	SC_METHOD (ser_combop);		
	sensitive << byte_in << xmt_done_ss << sclk_cntr << xmt_cnt16 << xmt_cnt << tc_xmt_cnt << xmt_done_s << bout << cnt << rcv_done_s << rcv_done_ss << rcv_cnt16 << rcv_cnt;	
	SC_METHOD (sclk_cntrp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (xmt_cnt16p);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (xmt_cntp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (xmt_donesp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (cntp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (valid_startp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (vld_str_debp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (rcv_cnt16p);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (rcv_cntp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (rcv_done_sp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (byte_inp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (rcv_bytep);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
	SC_METHOD (boutp);
	sensitive_pos << clk;
	sensitive_neg << rst_n;
   }
   
  void ser_combop ();
  void sclk_cntrp ();
  void xmt_cnt16p ();
  void xmt_cntp ();
  void xmt_donesp ();
  void cntp ();
  void boutp ();
  void valid_startp ();
  void vld_str_debp ();
  void rcv_cnt16p ();
  void rcv_cntp ();
  void rcv_done_sp ();
  void byte_inp ();
  void rcv_bytep ();

  };
