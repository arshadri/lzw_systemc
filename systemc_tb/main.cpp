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
// Description: Main block includes the "Serial Model" File and the 
//              "Testbench" File.
//
//*****************************************************************************

#include "testbench.cpp"
#include "lzw.cpp"
#include "ser_model.cpp" 
#include "systemc.h"

int sc_main(int argc, char* argv[])
{
  //Declare signals to be tied to the modules
  sc_signal< bool >          tx;                 // Serial transmit data
  sc_signal< bool >          ser_recv_done;      // Serial port data receive done
  sc_signal< bool >          init_cr;            // Initialize code value RAM
  sc_signal< bool >          init_lzw;           // Initialize LZW main state machine
  sc_signal< bool >          done_cr;            // Code value RAM initilization done
  sc_signal< bool >          lzw_done;           // LZW done with processing all data
  sc_signal< bool >          final_done;         // All transactions have finished   
  sc_signal< bool >          pwr_up;             // Power up for debug purpose on FPGA
  sc_signal< bool >          valid_start_deb;    // Valid start on Rx detected for debug
  sc_signal< bool >          rx;                 // Serial receive data
  sc_signal < bool >         ld_data;            // Load data into transmit shift register
  sc_signal < bool >         start_xmt;          // Start transmission of serial data
  sc_signal < bool >         tc_xmt_cnt;         // Terminal count for transmit bit counter
  sc_signal < bool >         tc_xmt_cnt16;       // Terminal count for holding the transmit bit for 16 clocks 
  sc_signal< bool >          rst;                // System reset, active high  
  sc_signal< sc_biguint <8> > din;               // Data input
  sc_signal<sc_biguint <8> >  dout;
  sc_signal <sc_biguint<8> >  mdl_rcv_byte;      // Receive byte from serial port
  
  sc_clock clk("clk",15,SC_NS);                  // Create a 66.66MHZ period clock signal
  sc_clock clk2("clk2",540,SC_NS);               // Create a 1.8432MHZ period clock signal

 /****************************************************************************
   Instantiate the LZW block
  ****************************************************************************/
  lzw lzw1("lzw11");
  lzw1.tx              (tx);
  lzw1.ser_recv_done   (ser_recv_done);
  lzw1.init_cr         (init_cr);      
  lzw1.init_lzw        (init_lzw);     
  lzw1.done_cr         (done_cr);      
  lzw1.lzw_done        (lzw_done);     
  lzw1.final_done      (final_done);     
  lzw1.pwr_up          (pwr_up);     
  lzw1.valid_start_deb (valid_start_deb);   
  
  // Inputs            
  lzw1.rx              (rx);
  lzw1.clk66           (clk); 
  lzw1.rst             (rst);

 /****************************************************************************
   Instantiate the Serial Model block
  ****************************************************************************/
  ser_model ser_model1("ser_model11");
  ser_model1.sin          (tx);
  ser_model1.byte_out          (din);
  ser_model1.clk          (clk);
  ser_model1.sclk         (clk2);
  ser_model1.rst          (rst);
 
  ser_model1.sout         (rx);
  ser_model1.dout         (dout);
  ser_model1.ld_data      (ld_data);
  ser_model1.tc_xmt_cnt   (tc_xmt_cnt);
  ser_model1.start_xmt    (start_xmt);
  ser_model1.tc_xmt_cnt16 (tc_xmt_cnt16);
  ser_model1.rcv_byte (mdl_rcv_byte);

/****************************************************************************
   Instantiate the testbench (test case)
 ****************************************************************************/

  testbench test1("TestBench1");
  test1.din          (din);
  test1.clk          (clk);
  test1.sclk         (clk2);
  test1.rst          (rst);
 
  test1.dout         (dout);
  test1.init_cr      (init_cr);
  test1.done_cr      (done_cr);
  test1.lzw_done     (lzw_done);
  test1.final_done   (final_done);
  test1.ld_data      (ld_data);
  test1.tc_xmt_cnt   (tc_xmt_cnt);
  test1.tc_xmt_cnt16 (tc_xmt_cnt16);
  test1.start_xmt    (start_xmt);
  
   //Dump vectors
    sc_trace_file *fp;                         // Declare VCD filepointer
    fp=sc_create_vcd_trace_file("wave");       // open(fp), create wave.vcd file
    sc_trace(fp,clk,"clk");                    // Add signals to trace file
    sc_trace(fp,clk2,"clk2"); 
    sc_trace(fp,dout,"dout");
    sc_trace(fp,din,"din");
    sc_trace(fp,rst,"rst");
    sc_trace(fp,tx,"tx");
    sc_trace(fp,rx,"rx");
    sc_trace(fp,ser_recv_done,"ser_recv_done");
    sc_trace(fp,init_cr,"init_cr");
    sc_trace(fp,init_lzw,"init_lzw");
    sc_trace(fp,done_cr,"done_cr");
    sc_trace(fp,lzw_done,"lzw_done");
    sc_trace(fp,final_done,"final_done");
    sc_trace(fp,pwr_up,"pwr_up");
    sc_trace(fp,valid_start_deb,"valid_start_deb");
    sc_trace(fp,ld_data,"ld_data");
    sc_trace(fp,tc_xmt_cnt,"tc_xmt_cnt");
    sc_trace(fp,tc_xmt_cnt16,"tc_xmt_cnt16");
    sc_trace(fp,start_xmt,"start_xmt");
    sc_trace(fp,mdl_rcv_byte,"mdl_rcv_byte");
	
	sc_start(10000000, SC_NS);
	
	sc_close_vcd_trace_file(fp);                // close(fp)

	return 0;
}