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
// Description: Second test vector as defined in document 
//
//*****************************************************************************   
#include "systemc.h"

SC_MODULE (testbench1)
{
  sc_out< sc_biguint <8> > din;            // Data input
  sc_out< bool >           rst;            // System reset
  sc_out< bool >           ld_data;        // Load data into transmit shift register
  sc_out< bool >           start_xmt;      // Start transmission of serial data
  sc_in < bool >           tc_xmt_cnt16;   // Terminal count for holding the transmit bit for 16 clocks
  
  sc_in< bool >            tc_xmt_cnt;     // Terminal count for transmit bit counter 
  sc_in< bool >            clk;            // System clock
  sc_in< bool >            sclk;           // Baud clock
  sc_in<sc_biguint <8> >   dout;
  sc_in< bool >            init_cr;
  sc_in< bool >            done_cr;
  sc_in< bool>             lzw_done;
  sc_in< bool>             final_done;



	SC_CTOR (testbench1)
   {
    SC_THREAD (process);
    sensitive_pos << sclk;
   }
	
	void process()
	{
	  
	  cout << "\tTEST: Reset asserted\n";
    rst = 1;
    ld_data = 0;
    start_xmt = 0;
    wait (890,SC_NS); 
    rst = 0;

    cout << "At time " << sc_time_stamp() << "::";
    cout << "\tTEST: Reset Deasserted" << endl;
  
    wait (984.75, SC_NS); // repeat 10 clock
    if (init_cr.read()) {
    cout << "At time " << sc_time_stamp() << "::";
    cout << "\tTEST: Init CR Asserted" << endl;	
    }
    else  {
    cout << "At time " << sc_time_stamp() << "::";
    cout << "\tTEST: Init CR Deasserted" << endl;	
    }
    wait (62084.7, SC_NS);  
    cout << "At time " << sc_time_stamp() << "::";
    cout << "\tTEST: Code RAM initialized" << endl;
	  
	  // Transmit ASCII code from serial port to FPGA
    wait (150, SC_NS); // repeat 10 clock
    ld_data = 1;
    start_xmt = 1;
    
    for (int i=0; i<4096; i=i+1) 
    { 
      din.write(0x63); // char c
      wait (540, SC_NS); // repeat 1 clock
      ld_data = 0; 
      while (!tc_xmt_cnt.read()) {
        wait(1,SC_NS);
      }
      start_xmt = 0;    
      wait (540, SC_NS); // repeat 1 clock
      
      ld_data = 1;
      start_xmt = 1;
    }
    
    //din.write(0x1A); // End of file code for file size less than 4K
wait (540, SC_NS); // repeat 1 clock
    ld_data = 0;    
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;
     while (!lzw_done.read()) {
      wait(1,SC_NS);
    }
    
     while (!final_done.read()) {
      wait(1,SC_NS);
    }

    wait(300, SC_NS);
    wait(200, SC_NS);
	}
	
};