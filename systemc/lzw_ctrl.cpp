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
// Description: LZW controller block.
//
//*****************************************************************************

#include "systemc.h"
#include "lzw_ctrl.h" 
  

void lzw_ctrl::process_clk ()
  {
    if (!rst_n.read())
      curr_st.write(LIDLE);
    else
      curr_st.write(nxt_st);
  }
  
 void lzw_ctrl::process_curr_st ()
  {
    enb_cvram.write(false);
    web_cvram.write(false);
    inc_cvbaddr.write(false);
    done_cr_st.write(false);
    clr_acntr.write(false);
    enb_ioram.write(false);
    web_ioram.write(false);
    enb_outram.write(false);
    web_outram.write(false);
    shift_char.write(false);
    gen_hash.write(false);
    ena_cvram.write(true);
    wea_cvram.write(false);
    inc_cvadata.write(false);
    wea_acram.write(false);
    wea_pcram.write(false);
    recal_hash_st.write(false);          
    write_data.write(false);         
    read_data.write(false);
    done_lzw_st.write(false);
    inc_ioraddr.write(false);
    inc_outraddr.write(false);
    clr_ioacntr.write(false);
    mux_code_val.write(false);
    write_sp.write(false);
   
    switch(curr_st.read())
    {
      case LIDLE:
      {
        if (init_cr.read())
        {
          enb_cvram.write(true);
          web_cvram.write(true);
          inc_cvbaddr.write(true);
          ena_cvram.write(false);
          nxt_st.write(LINIT_CR);
        }
        else
          nxt_st.write(LIDLE);
      break;
      }
      case LINIT_CR:          // Initiliaze Code RAM
      {
        if (tc_cvactr.read())
        {
          done_cr_st.write(true);
          clr_acntr.write(true);
          nxt_st.write(WT_LZWST);
        }
        else
        {
          web_cvram.write(true);
          enb_cvram.write(true);
          inc_cvbaddr.write(true);
          ena_cvram.write(false);
          nxt_st.write(LINIT_CR);
        }
      break;
      }
      case WT_LZWST:          // Wait for LZW start
      {
        if (init_lzw.read())
        {
          enb_ioram.write(true);
          nxt_st.write(WT_DST1);
        }
        else
          nxt_st.write(WT_LZWST);
      break;
      }
      case WT_DST1:          // Wait for Data 1
      {
        inc_ioraddr.write(true);
        shift_char.write(true);
        nxt_st.write(RD_2NDCHAR);
      break;
      }
      case RD_2NDCHAR:          // Read second character from IO RAM
      {
        enb_ioram.write(true);
        nxt_st.write(WT_DST2);
      break;
      } 
      case WT_DST2:          // Wait for Data 2
      {
        gen_hash.write(true);
        nxt_st.write(GEN_HASH);
      break;
      }
      case GEN_HASH:           // Generate HASH
      {
        ena_cvram.write(true);
        nxt_st.write(WT_HASH);
      break;
      }
      case WT_HASH:           // Wait for HASH result
      {
        if (not_in_mem.read())    // Not in memory write data into all RAM's
        {                
          wea_cvram.write(true);
          inc_cvadata.write(true);
          wea_acram.write(true);
          wea_pcram.write(true);
          nxt_st.write(WR_OREG);
        }
       else if (match.read()) // Match in dictionary 
        {
          mux_code_val.write(true);
          shift_char.write(true);
          nxt_st.write(CHK_CNT);
        }
        else if (in_code_mem.read())   // Match in code memory 
        {
          mux_code_val.write(true);
          nxt_st.write(WR_OREG);
        }
        else if (collis.read())  // Collision generate during hash, recaluclate
        {
          recal_hash_st.write(true);
          nxt_st.write(WT_RHASH);
        }
        else 
          nxt_st.write(WT_HASH);
      break;
      }
      case WT_RHASH:           // Wait for recalculate HASH result
      {
        if (not_in_mem.read())
        {              
          wea_cvram.write(true);
          inc_cvadata.write(true);
          wea_acram.write(true);
          wea_pcram.write(true);
          nxt_st.write(WR_OREG);
        }
        else if (match.read()) // Match in dictionary 
        {
          mux_code_val.write(true);
          shift_char.write(true);
          //nxt_st.write(CHK_CNT);
          nxt_st.write(RD_2NDCHAR);
        }
        else if (in_code_mem.read())   // Match in code memory 
        {
          nxt_st.write(WR_OREG);
        }
        else if (collis.read())  // Wait for recalculate HASH result
        {
          recal_hash_st.write(true);
          nxt_st.write(WT_HASH);
        }
        else 
          nxt_st.write(WT_RHASH);
      break;
      }
      case WR_OREG:          // Write to output data register
      {
        if (in_code_mem.read())
          mux_code_val.write(true);
        else
          mux_code_val.write(false);
        write_data.write(true);
        shift_char.write(true);
        nxt_st.write(RD_OREG);
      break;
      }
      case RD_OREG:          // Read from output data register and write to IORAM
      {
        read_data.write(true);
        web_outram.write(true);
        enb_outram.write(true);
        inc_outraddr.write(true);
        nxt_st.write(RD_OREG2);
      break;
      }
      case RD_OREG2:          // If greater than 8-bits data than read again
      {
        if (valid_dcnt.read())
        {
          read_data.write(true);
          web_outram.write(true);
          enb_outram.write(true);
          inc_outraddr.write(true);
          nxt_st.write(RD_OREG2);
        }
        else 
        {
          enb_outram.write(false);
          web_outram.write(false);
          inc_outraddr.write(false);
          nxt_st.write(CHK_CNT);
        }
      break;
      }
      case CHK_CNT:          // Check that IO address counter is at max. value or not
      {
        if (write_sp_r.read())
        {
          nxt_st.write(FL_OUT);
        }
        else if (tc_ioractr.read() & !match.read() & !write_sp_r.read())
        {
          write_sp.write(true);
          nxt_st.write(SP_CHR);
        }
        else if (tc_ioractr.read() & match.read() & !write_sp_r.read())
        {
          inc_outraddr.write(true);
          write_sp.write(true);
          nxt_st.write(SP_CHR);
        }
        else if (match.read()) 
        {
          inc_ioraddr.write(true);
          nxt_st.write(RD_2NDCHAR);
        }
        else   //~match case
        {
          inc_ioraddr.write(true);
          nxt_st.write(RD_2NDCHAR);
        }
      break;
      }
      case SP_CHR:           // Write special character
      {        
        nxt_st.write(RD_OREG);
      break;
      }
      case FL_OUT:           // All transmission finished
      {  
       if (tc_outreg.read())
       {
        nxt_st.write(LDONE);
       }
       else   // Less than byte left in outreg, flush it
       {
         read_data.write(true);
         web_outram.write(true);
         enb_outram.write(true);
         done_lzw_st.write(true);
         nxt_st.write(LDONE);
       }
      break;
      }
      case LDONE:           // All transmission finished
      {  
        nxt_st.write(LIDLE);
        done_lzw_st.write(true);
      break;
      }
      default: nxt_st.write(LIDLE);
      break;
    }
  }
  
  /****************************************************************************
   Counter for generating the address to IO RAM
   This address will be used to read the received byte from IO RAM
  ****************************************************************************/
  void lzw_ctrl::process_clk1 ()
  {
    if (!rst_n.read())
      ioaddr_cntr.write(0x000);
    else if (clr_ioacntr.read())
      ioaddr_cntr.write(0x000);
    else if (inc_ioraddr.read())
      ioaddr_cntr.write(ioaddr_cntr + 1);
  }
  
  void lzw_ctrl::process_tc_ioractr ()
  {
    tc_ioractr = (ioaddr_cntr.read() == char_cnt.read());
  }
  
  void lzw_ctrl::process_addrb_ioram ()
  {
    addrb_ioram = ioaddr_cntr.read();
  }
 
  /****************************************************************************
   Counter for generating the address to out RAM
   This address will be used to write the lzw byte to out RAM
  ****************************************************************************/
  void lzw_ctrl::process_clk2 ()
  {
    if (!rst_n.read())
      outaddr_cntr.write(0x000);
    else if (inc_outraddr.read())
      outaddr_cntr.write(outaddr_cntr + 1);
  }
  
  void lzw_ctrl::process_addrb_outram ()
  {
    addrb_outram = outaddr_cntr.read();
  }
  
  void lzw_ctrl::process_outram_cnt ()
  {
    outram_cnt = outaddr_cntr.read();
  }
  
  
  /****************************************************************************
   Counter for generating the address to Code value RAM
   This address will be used to initiliaze the data and write code value data
   to RAM.
  ****************************************************************************/
  void lzw_ctrl::process_clk3 ()
  {
    if (!rst_n.read())
      inc_cvbaddr_d.write(false);
    else 
      inc_cvbaddr_d.write(inc_cvbaddr);
  }
  
  void lzw_ctrl::process_clk4 ()
  {
    if (!rst_n.read())
      addr_cntr.write(0x000);
    else if (clr_acntr.read())
      addr_cntr.write(0x000);
    else if (inc_cvbaddr_d.read())
      addr_cntr.write(addr_cntr + 1);
  }
  
  void lzw_ctrl::process_tc_cvactr ()
  {
    tc_cvactr = (addr_cntr.read() == 0x7ff);
  }
  
  void lzw_ctrl::process_addrb_cvram ()
  {
    addrb_cvram = (0,0,addr_cntr.read());
  }
  
  //assign addrb_cvram = {2'b00,addr_cntr[10:0]}; AFZAL
  
  /****************************************************************************
   Counter for generating the data to the Code value RAM
  ****************************************************************************/
  void lzw_ctrl::process_clk5 ()
  {
    if (!rst_n.read())
      data_cntr.write(0x100);
    else if (done_lzw_st.read())
      data_cntr.write(0x100);
    else if (inc_cvadata.read())
      data_cntr.write(data_cntr + 1);
  }
  
  void lzw_ctrl::process_wr_cvdataa ()
  {
    wr_cvdataa = data_cntr.read();
  }
  
  // Initilization of the code value RAM has ended
  void lzw_ctrl::process_clk6 ()
  {
    if (!rst_n.read())
      done_cr.write(false);
    else
      done_cr.write(done_cr_st);
  }
  
  // LZW for all data has ended
  void lzw_ctrl::process_clk7 ()
  {
    if (!rst_n.read())
      lzw_done.write(false);
    else
      lzw_done.write(done_lzw_st);
  }
  
  // LZW for all data has ended
  void lzw_ctrl::process_clk8 ()
  {
    if (!rst_n.read())
      recal_hash.write(false);
    else
      recal_hash.write(recal_hash_st);
  }
  
  // Delayed version of write special character
  void lzw_ctrl::process_clk9 ()
  {
    if (!rst_n.read())
      write_sp_r.write(false);
    else if (done_lzw_st.read())
      write_sp_r.write(false);
    else if (write_sp.read())
      write_sp_r.write(true);
  }
  