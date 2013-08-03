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
// Description: Third test vector as defined in document 
//
//*****************************************************************************   
#include "systemc.h"

SC_MODULE (testbench2)
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


	 SC_CTOR (testbench2)
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
    din.write(0x41); // char A
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    
    din.write(0x42); // char B
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x43); // char C
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x44); // char D
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x45); // char E
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;  
    din.write(0x46); // char F
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x47); // char G
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x48); // char H
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x49); // char I
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x4a); // char J
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x4b); // char K
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x4c); // char L
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x4d); // char M
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x4e); // char N
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x4f); // char O
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x50); // char P
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x51); // char Q
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x52); // char R
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x53); // char S
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x54); // char T
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x55); // char U
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x56); // char V
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x57); // char W
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x58); // char X
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x59); // char Y
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x5A); // char Z
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x61); // char a
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x62); // char b
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
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
    din.write(0x64); // char d
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x65); // char e
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x66); // char f
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x67); // char g
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x68); // char h
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x69); // char i
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x6a); // char j
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x6b); // char k
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x6c); // char l
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x6d); // char m
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x6e); // char n
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x6f); // char o
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x70); // char p
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x71); // char q
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x72); // char r
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x73); // char s
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x74); // char t
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x75); // char u
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x76); // char v
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x77); // char w
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x78); // char x
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x79); // char y
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x7a); // char z
    wait (540, SC_NS); // repeat 1 clock
    ld_data = 0; 
    while (!tc_xmt_cnt.read()) {
      wait(1,SC_NS);
    }
    start_xmt = 0;    
    wait (540, SC_NS); // repeat 1 clock
  
    ld_data = 1;
    start_xmt = 1;
    din.write(0x0D); // End of file code for file size less than 4K
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