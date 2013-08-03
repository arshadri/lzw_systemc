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
// Description: LZW encoder control block.
//
//*****************************************************************************
     
#include "systemc.h"

SC_MODULE (lzw_ctrl)      
{
  /****************************************************************************
   Outputs
  ****************************************************************************/
  sc_out< bool >        done_cr;           // Code value RAM initilization done
  sc_out< bool >        lzw_done;          // LZW done with processing all data
  sc_out< bool >        gen_hash;          // Generate Hash 
  sc_out< bool >        recal_hash;        // Recalculate hash due to collision
  sc_out< sc_biguint <12> > addrb_ioram;   // Address for IO RAM port B
  sc_out< bool >        enb_ioram;         // Enable IO RAM port B 
  sc_out< bool >        web_ioram;         // Write enable IO RAM port B
  sc_out< sc_biguint <12> > addrb_outram;  // Address for out RAM port B
  sc_out< bool >        enb_outram;        // Enable out RAM port B 
  sc_out< bool >        web_outram;        // Write enable out RAM port B
  sc_out< sc_biguint <13> > addrb_cvram;   // Address for CV RAM port B
  sc_out< bool >        enb_cvram;         // Enable code value RAM port B 
  sc_out< bool >        web_cvram;         // Write enable code value RAM port B
  sc_out< sc_biguint <13> > wr_cvdataa;    // Write data for code value RAM port A
  sc_out< bool >        ena_cvram;         // Enable code value RAM port A
  sc_out< bool >        wea_cvram;         // Write enable code value RAM port A
  sc_out< bool >        wea_acram;         // Write Enable append char RAM port A  
  sc_out< bool >        wea_pcram;         // Write Enable prefix code char RAM port A 
  sc_out< bool >        read_data;         // Read data from output register  
  sc_out< bool >        write_data;        // Write data into output register  
  sc_out< bool >        shift_char;        // Shift character from char. to string reg.
  sc_out< bool >        mux_code_val;      // Mux code value into string register
  sc_out< sc_biguint <12> > outram_cnt;    // Output RAM data count
  sc_out< bool >        write_sp;          // Write special code into output register
   
  /****************************************************************************
   Inputs
  ****************************************************************************/
  sc_in< bool >         init_cr;            // Initialize code value RAM
  sc_in< bool >         init_lzw;           // Initialize LZW main state machine  
  sc_in< sc_biguint <12> > char_cnt;        // Number of characters received
  sc_in< bool >         not_in_mem;         // Address not in code value RAM  
  sc_in< bool >         in_code_mem;        // Address in code value RAM  
  sc_in< bool >         match;              // Match in dictionary  
  sc_in< bool >         collis;             // Collision   
  sc_in< bool >         valid_dcnt;         // Valid data count in outreg  
  sc_in< bool >         tc_outreg;          // Terminal count output register 
  sc_in< bool >         clk;                // System clock
  sc_in< bool >         rst_n;              // System reset, active low
  
  enum vm_state
  { 
  LIDLE      ,
  LINIT_CR   ,           
  WT_LZWST   ,           
  WT_DST1    ,           
  RD_2NDCHAR ,           
  WT_DST2    ,           
  GEN_HASH   ,           
  WT_HASH    ,           
  WT_RHASH   ,           
  WR_OREG    ,            
  RD_OREG    ,             
  RD_OREG2   ,             
  CHK_CNT    ,              
  SP_CHR     ,            
  FL_OUT     ,   
  LDONE            
  };
  
  sc_signal < vm_state > nxt_st;
  sc_signal < vm_state > curr_st;
	
	SC_CTOR(lzw_ctrl) 
	{
	SC_METHOD (process_clk);
    sensitive_pos (clk);
	SC_METHOD (process_curr_st);
    sensitive << curr_st << init_cr << tc_cvactr << init_lzw << not_in_mem << match << in_code_mem << collis << valid_dcnt << write_sp_r << tc_ioractr << tc_outreg;
  SC_METHOD (process_clk1);
    sensitive_pos (clk);
  SC_METHOD (process_tc_ioractr);
    sensitive << ioaddr_cntr << char_cnt;
  SC_METHOD (process_addrb_ioram);
    sensitive << ioaddr_cntr;
  SC_METHOD (process_clk2);
    sensitive_pos (clk);
  SC_METHOD (process_addrb_outram);
    sensitive << outaddr_cntr;
  SC_METHOD (process_outram_cnt);
    sensitive << outaddr_cntr;
  SC_METHOD (process_clk3);
    sensitive_pos (clk);
  SC_METHOD (process_clk4);
    sensitive_pos (clk);
  SC_METHOD (process_tc_cvactr);
    sensitive << addr_cntr;
  SC_METHOD (process_addrb_cvram);
    sensitive << addr_cntr;  
  SC_METHOD (process_clk5);
    sensitive_pos (clk);
  SC_METHOD (process_wr_cvdataa);
    sensitive << data_cntr;      
  SC_METHOD (process_clk6);
    sensitive_pos (clk);
  SC_METHOD (process_clk7);
    sensitive_pos (clk);
  SC_METHOD (process_clk8);
    sensitive_pos (clk);
  SC_METHOD (process_clk9);
    sensitive_pos (clk);
  
  }  
 
  /****************************************************************************
   Internal declarations
  ****************************************************************************/   
  sc_signal < bool >           tc_ioractr;        // Terminal count for IO RAM address ctr  
  sc_signal < bool >           tc_cvactr;         // Terminal count for CV RAM address ctr  
 
  sc_signal < bool >            done_cr_st;        // Done with code value RAM init., early
  sc_signal < bool >            inc_ioraddr;       // Increment IO RAM address
  sc_signal < bool >            inc_outraddr;      // Increment out RAM address
  sc_signal < bool >            done_lzw_st;       // Done with LZW,early
  sc_signal < sc_biguint <13> > data_cntr;         // Data counter for CV RAM data port A
  sc_signal < bool >            inc_cvbaddr;       // Increment code value RAM port B address
  sc_signal < bool >            inc_cvbaddr_d;     // Increment code value RAM port B address delayed
  sc_signal < bool >            clr_acntr;         // Clear address counter for CV RAM
  sc_signal < bool >            recal_hash_st;     // Recalculate hash early
  sc_signal < bool >            inc_cvadata;       // Increment code value RAM port A data
  sc_signal < sc_biguint <11> > addr_cntr;         // Address counter for CV RAM address
  sc_signal < sc_biguint <12> > ioaddr_cntr;       // Address counter for IO RAM address
  sc_signal < sc_biguint <12> > outaddr_cntr;      // Address counter for out RAM address
  sc_signal < bool >            clr_ioacntr;       // Clear address counter for IO RAM 
  sc_signal < bool >            write_sp_r;        // Write special code into output register
  
  
  
  
  void process_clk ();
  void process_curr_st ();
  void process_clk1 ();
  void process_tc_ioractr ();
  void process_addrb_ioram ();
  void process_clk2 ();
  void process_addrb_outram ();
  void process_outram_cnt ();
  void process_clk3 ();
  void process_clk4 ();
  void process_tc_cvactr ();
  void process_addrb_cvram ();
  void process_clk5 ();
  void process_wr_cvdataa ();
  void process_clk6 ();
  void process_clk7 ();
  void process_clk8 ();
  void process_clk9 ();


  
};