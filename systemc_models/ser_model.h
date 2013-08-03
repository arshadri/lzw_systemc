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
#include "systemc.h"

SC_MODULE (ser_model)      
{
  /****************************************************************************
   Input/Outputs
  ****************************************************************************/
  // Outputs
  sc_out <bool>                sout;           // Serial output
  sc_out <sc_biguint <8> >     dout;           // Data to be transmitted
  sc_out < bool >              tc_xmt_cnt;     // Terminal count for transmit bit counter
  sc_out < bool >              tc_xmt_cnt16;   // Terminal count for holding the transmit bit for 16 clocks
  sc_out < sc_biguint <8> >    rcv_byte;       // Received data byte
  // Inputs
  sc_in  <bool>                clk;            // System clock
  sc_in  <bool>                sclk;           // Baud clock
  sc_in  <bool>                rst;            // reset
  sc_in  <bool>                sin;            // Serial data in
  sc_in  <sc_biguint <8> >     byte_out;       // Byte to be transmitted
  sc_in < bool >               ld_data;        // Load data into transmit shift register
  sc_in < bool >               start_xmt;      // Start transmission of serial data
	 
  /****************************************************************************
   Internal declarations
  ****************************************************************************/   
  sc_signal < sc_biguint <9> >    byte_in;        // Byte received 
  sc_signal < sc_biguint <10> >   bout;           // Byte to be transmitted with one start and stop bit
  sc_signal < sc_biguint <4> >    xmt_cnt;        // Transmit bit count
  sc_signal < sc_biguint <4> >    xmt_cnt16;      // Counter for holding the transmit data bit for 16 clock cycles
  sc_signal < sc_biguint <4> >    cnt;            // Counter for detecting valid start bit
  sc_signal < bool >              valid_start;    // Valid start bit detected on received data
  sc_signal < sc_biguint <4> >    rcv_cnt;        // Received bit count
  sc_signal < sc_biguint <4> >    rcv_cnt16;      // Receive data bit is counted for 16 clocks for valid reception
  sc_signal < sc_biguint <5> >    cnt_cmd_bytes;  // Count number of command bytes received.
  sc_signal < sc_biguint <16> >   disp_cnt;       // Display count
  sc_signal < bool >              tc;             // Terminal count
  sc_signal < bool >              tc_rcv_cnt;     // Terminal count for receive bit counter
  sc_signal < bool >              tc_rcv_cnt16;   // Terminal count for holding the receive bit for 16 clocks
  sc_signal < sc_biguint <8> >    byte_in_int2;
  
         
	
	SC_CTOR(ser_model) 
	{
	SC_METHOD (process_rcv_byte);
	  sensitive << byte_in;
  SC_METHOD (process_thread_initial);
  sensitive_pos << rst;
  SC_METHOD (process_clk1);
    sensitive_pos (sclk);
  SC_METHOD (process_tc_xmt_cnt16);
    sensitive << xmt_cnt16;
  SC_METHOD (process_clk2);
    sensitive_pos (sclk);
  SC_METHOD (process_tc_xmt_cnt);
    sensitive << xmt_cnt;
  SC_METHOD (process_clk3);
    sensitive_pos (sclk);
  SC_METHOD (process_bout);
    sensitive << bout;
  SC_METHOD (process_clk4);
    sensitive_pos (sclk);
  SC_METHOD (process_tc);
    sensitive << cnt;
  SC_METHOD (process_valid_start);
    sensitive << tc_rcv_cnt << tc << rst;
  SC_METHOD (process_clk5);
    sensitive_pos (sclk);
  SC_METHOD (process_tc_rcv_cnt16);
    sensitive << rcv_cnt16;
  SC_METHOD (process_clk6);
    sensitive_pos (sclk);
  SC_METHOD (process_tc_rcv_cnt);
    sensitive << rcv_cnt;
  SC_METHOD (process_byte_in_int);
    sensitive << byte_in_int2;
  SC_METHOD (process_clk7);
    sensitive_pos (sclk);
  SC_METHOD (process_clk8)
    sensitive_pos (sclk);
    sensitive_pos (rst);
  SC_METHOD (process_read);
    sensitive << byte_in;
  }  
 

  void process_rcv_byte ();
  void process_thread_initial ();
  void process_clk1 ();
  void process_tc_xmt_cnt16 ();
  void process_clk2 ();
  void process_tc_xmt_cnt ();
  void process_clk3 ();
  void process_bout ();
  void process_clk4 ();
  void process_tc ();
  void process_valid_start ();
  void process_clk5 ();
  void process_tc_rcv_cnt16 ();
  void process_clk6 ();
  void process_tc_rcv_cnt ();
  void process_byte_in_int ();
  void process_clk7 ();
  void process_clk8 ();
  void process_read ();  
};