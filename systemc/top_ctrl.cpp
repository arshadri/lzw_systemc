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
#include "top_ctrl.h" 
  
  void top_ctrl::process_curr_st ()     
  {
   init_cr_st.write(false);   
   inc_ioraddr.write(false);  
   inc_outraddr.write(false);  
   init_lzw_st.write(false);  
   start_xmt.write(false);    
   ena_ioram.write(false);    
   wea_ioram.write(false);   
   clr_acntr.write(false);     
   ena_outram.write(false);  
   clr_aoutcntr.write(false);
   done.write(false); 
   idle.write(false); 
   
   switch(curr_st.read())
   {
     case IDLE:
       idle.write(true);
       init_cr_st.write(true);
       nxt_st.write(INIT_CR);
       break;
     case INIT_CR:          // Initiliaze Code RAM
      {
        if (done_cr.read() == 1)
          nxt_st.write(WT_RST);
        else
          nxt_st.write(INIT_CR);
        break;
      }
      case WT_RST:          // Wait Receive State
      {
        nxt_st.write(WT_RC);
        break;
      }
      case WT_RC:           // Wait for receive character
      {
        if (rcv_done.read() == 1)
        {
          //cout << "At time " << sc_time_stamp() << "::";
          //cout << "\tTOP_CTRL: WT_RC, receive done" << endl;
          ena_ioram.write(true);
          wea_ioram.write(true);
          nxt_st.write(WT_ST);
        }
        else if (tc_ioractr.read() == 1)
        {
          //cout << "At time " << sc_time_stamp() << "::";
          //cout << "\tTOP_CTRL: WT_RC, tc_ioractr done" << endl;
          init_lzw_st.write(true);
          nxt_st.write(LZWDONE);
        }
        else
          nxt_st.write(WT_RC);
        break;
      }
      case WT_ST:           // Wait  State
      {
        inc_ioraddr.write(true);
        nxt_st.write(WT_RST);
        break;
      }
      case LZWDONE:         // Wait for LZW Done
      {
        if (lzw_done.read() == 1)
        {
          nxt_st.write(WT_TST);
          clr_acntr.write(true);
        }
        else
          nxt_st.write(LZWDONE);
        break;
      }
      case WT_TST:          // Wait Transmit State
      {
        nxt_st.write(WT_TC1);
        start_xmt.write(true);
        ena_outram.write(true);
        break;
      }
      case WT_TC1:           // Wait for transmit character
      {
        if (xmt_done.read() == 1)
        {
          start_xmt.write(false);
          nxt_st.write(WT_TC);
        }      
        else
        {
          start_xmt.write(true);
          nxt_st.write(WT_TC1);
        }
        break;
      }
      case WT_TC:           // Wait for transmit character
      {
        if ((tc_outractr.read() == 1) & (xmt_done.read() == 0))
          nxt_st.write(DONE);
        else if ((tc_outractr.read() == 0) & (xmt_done.read() == 0))
        {
          inc_outraddr.write(true);
          ena_outram.write(true);
          nxt_st.write(WT_TST);
        }        
        else
          nxt_st.write(WT_TC);
        break;
      }
      case DONE:           // All transmission finished
      {  
        done.write(true); 
        nxt_st.write(DONE);
        break;
      }
      default: nxt_st.write(IDLE);
        break;
   
   }
   
  }

void top_ctrl::process_clk ()
{
 if (rst_n.read() == 0)
   curr_st.write(IDLE);
 else {
   curr_st.write(nxt_st);
 }
}

  /****************************************************************************
   Counter for generating the address to IO RAM
   This address will be used to write the received byte to IO RAM, and read
   a byte from IO RAM for transmission.
  ****************************************************************************/
  void top_ctrl::process_clk1 ()
  {
    if (rst_n.read () == 0)
      addr_cntr.write(0x000);
    else if (clr_acntr.read())
      addr_cntr.write(0x000);
    else if (inc_ioraddr.read())
      addr_cntr.write(addr_cntr + 1);
  }
  
  void top_ctrl::process_tc_ioractr ()
  {
    
   cout << "At time " << sc_time_stamp() << "::";
   cout << "\tTOP_CTRL:char_in " << char_in.read() << endl;
    tc_ioractr = (addr_cntr.read() == 0xfff) | (char_in.read() == 0x0D);
  }
  
  void top_ctrl::process_addra_ioram ()
  {
    addra_ioram = addr_cntr.read();
  }
  
  void top_ctrl::process_char_cnt ()
  {
    char_cnt = addr_cntr.read();
  }
  
  /****************************************************************************
   Counter for generating the address to out RAM
   This address will be used to read the lzw byte from out RAM
  ****************************************************************************/
  void top_ctrl::process_clk2 ()
  {
    if (rst_n.read () == 0)
      addr_outcntr.write(0x000);
    else if (clr_aoutcntr.read())
      addr_outcntr.write(0x000);
    else if (inc_outraddr.read())
      addr_outcntr.write(addr_outcntr + 1);
  }
  
  void top_ctrl::process_tc_outractr ()
  {
    tc_outractr = (addr_outcntr.read() == (outram_cnt.read() + 1));
  }
  
  void top_ctrl::process_addra_outram ()
  {
    addra_outram = addr_outcntr.read();
  }
  
  // Start the initilization of the code value RAM
  void top_ctrl::process_clk3 ()
  {
    if (rst_n.read () == 0)
      init_cr.write(false);
    else
      init_cr.write(init_cr_st);
  }
  
  // Start the LZW block
  void top_ctrl::process_clk4 ()
  {
    if (rst_n.read () == 0)
      init_lzw.write(false);
    else
      init_lzw.write(init_lzw_st);
  }

  /****************************************************************************
   Outputs for debugging on the FPGA board
  ****************************************************************************/  
  void top_ctrl::process_clk5 ()
  {
    if (rst_n.read() == 0)
      pwr_up.write(false);
    else  if (idle.read())        
      pwr_up.write(true);
  }
  
  // All data has been received
  void top_ctrl::process_clk6 ()
  {
    if (rst_n.read() == 0)
      ser_recv_done.write(false);
    else if (tc_ioractr.read())
      ser_recv_done.write(true);
  }
  
  // Start the initilization of the code value RAM
  void top_ctrl::process_clk7 ()
  {
    if (rst_n.read() == 0)
      init_cr_out.write(false);
    else if (init_cr_st.read())
      init_cr_out.write(true);
  }
  
  // Start the LZW block
  void top_ctrl::process_clk8 ()
  {
    if (rst_n.read () == 0)
      init_lzw_out.write(false);
    else  if (init_lzw_st.read())
      init_lzw_out.write(true);
  }
  
  // Finished the initilization of the code value RAM
  void top_ctrl::process_clk9 ()
  {
    if (rst_n.read() == 0)
      done_cr_out.write(false);
    else if (done_cr.read())
      done_cr_out.write(true);
  }
  
  // Finished the LZW block
  void top_ctrl::process_clk10 ()
  {
    if (rst_n.read() == 0)
      lzw_done_out.write(false);
    else  if (lzw_done.read())
      lzw_done_out.write(true);
  }
  
  void top_ctrl::process_final_done ()
  {
    final_done = done.read();
  }
  