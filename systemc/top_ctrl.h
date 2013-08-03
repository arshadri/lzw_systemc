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
// Description: Top level control state machine for writing input/output RAM 
//              and triggering the LZW encoder.
//
//***************************************************************************** 
    
#include "systemc.h"

SC_MODULE (top_ctrl)      
{
  /****************************************************************************
   Outputs
  ****************************************************************************/
  sc_out< bool >        init_cr;           // Initialize code value RAM
  sc_out< bool >        init_lzw;          // Initialize LZW main state machine
  sc_out< sc_biguint <12> > char_cnt;      // Number of characters received
  sc_out< bool >        start_xmt;         // Start transmission of serial byte
  sc_out< sc_biguint <12> > addra_ioram;   // Address for IO RAM port A
  sc_out< bool >        ena_ioram;         // Enable IO RAM port A 
  sc_out< bool >        wea_ioram;         // Write enable IO RAM port A
  sc_out< sc_biguint <12> > addra_outram;  // Address for out RAM port A
  sc_out< bool >        ena_outram;        // Enable out RAM port A 
  sc_out< bool >        ser_recv_done;     // Serial port data receive done debug out
  sc_out< bool >        init_cr_out;       // Initiliaze code value ram debug out
  sc_out< bool >        done_cr_out;       // Done initiliaze code value ram debug out
  sc_out< bool >        init_lzw_out;      // LZW start debug out
  sc_out< bool >        lzw_done_out;      // LZW done debug out
  sc_out< bool >        final_done;        // All transactions have finished
  sc_out< bool >        pwr_up;            // State machine is in idle state after rst.
   
  /****************************************************************************
   Inputs
  ****************************************************************************/
  sc_in< bool >         done_cr;            // Code value RAM initilization done
  sc_in< bool >         lzw_done;           // LZW done with processing all data
  sc_in< bool >         rcv_done;           // Receive character done
  sc_in< bool >         xmt_done;           // Serial byte transmission done
  sc_in< sc_biguint <8> > char_in;          // Received character
  sc_in< sc_biguint <12> > outram_cnt;      // Output RAM data count
  sc_in< bool >         clk;                // System clock
  sc_in< bool >         rst_n;              // System reset, active low
  
  
  enum vm_state
  { 
  IDLE    ,
  INIT_CR ,            
  WT_RST  ,            
  WT_RC   ,          
  WT_ST   ,              
  LZWDONE ,            
  WT_TST  ,          
  WT_TC1  ,             
  WT_TC   ,            
  DONE      
  };
  
  sc_signal < vm_state > nxt_st;
  sc_signal < vm_state > curr_st;
	
	SC_CTOR(top_ctrl) 
	{
	SC_METHOD (process_curr_st);
    sensitive << curr_st << done_cr << rcv_done << tc_ioractr << lzw_done << xmt_done << tc_outractr;
  SC_METHOD (process_clk);
    sensitive_pos (clk);
  SC_METHOD (process_clk1);
    sensitive_pos (clk);
  SC_METHOD (process_tc_ioractr);
    sensitive << addr_cntr << char_in;
  SC_METHOD (process_addra_ioram);
    sensitive << addr_cntr;
  SC_METHOD (process_char_cnt);
    sensitive << addr_cntr;
  SC_METHOD (process_clk2);
    sensitive_pos (clk);
  SC_METHOD (process_tc_outractr);
    sensitive << addr_outcntr << outram_cnt;
  SC_METHOD (process_addra_outram);
    sensitive << addr_outcntr;
  SC_METHOD (process_clk3);
    sensitive_pos (clk);
  SC_METHOD (process_clk4);
    sensitive_pos (clk);
  SC_METHOD (process_clk5);
    sensitive_pos (clk);
  SC_METHOD (process_clk6);
    sensitive_pos (clk);
  SC_METHOD (process_clk7);
    sensitive_pos (clk);
  SC_METHOD (process_clk8);
    sensitive_pos (clk);
  SC_METHOD (process_clk9);
    sensitive_pos (clk);
  SC_METHOD (process_clk10);
    sensitive_pos (clk);
  SC_METHOD (process_final_done);
    sensitive << done;
  
  }  
 
  /****************************************************************************
   Internal declarations
  ****************************************************************************/   
  sc_signal < bool >            tc_ioractr;        // Terminal count for IO RAM address ctr
  sc_signal < bool >            tc_outractr;       // Terminal count for out RAM address ctr
  
  
  sc_signal < bool >             init_cr_st;       // Initialize code value RAM, early
  sc_signal < bool >             inc_ioraddr;      // Increment IO RAM address
  sc_signal < bool >             inc_outraddr;     // Increment out RAM address
  sc_signal < bool >             init_lzw_st;      // Initialize LZW main state machine,early
  sc_signal < sc_biguint <12> > addr_cntr;         // Address counter for IO RAM address
  sc_signal < bool >             clr_acntr;        // Clear address counter
  sc_signal < sc_biguint <12> > addr_outcntr;      // Address counter for out RAM address
  sc_signal < bool >             clr_aoutcntr;     // Clear address counter
  sc_signal < bool >             done;             // done
  sc_signal < bool >             idle;             // State machine is in idle state after rst.
  
  void process_curr_st ();     
  void process_clk ();
  void process_clk1 ();
  void process_tc_ioractr ();
  void process_addra_ioram ();
  void process_char_cnt ();
  void process_clk2 ();
  void process_tc_outractr ();
  void process_addra_outram ();
  void process_clk3 ();
  void process_clk4 ();
  void process_clk5 ();
  void process_clk6 ();
  void process_clk7 ();
  void process_clk8 ();
  void process_clk9 ();
  void process_clk10 ();
  void process_final_done ();

  
};