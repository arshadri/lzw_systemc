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
// Description: LZW encoder block, consists of controller and various RAM's.
//
//*****************************************************************************   
   
  #include "systemc.h" 
  
  /****************************************************************************
   LZW encoder implementation
  ****************************************************************************/
  SC_MODULE(lzw_enc) {
  // Outputs
       sc_out <sc_biguint<8> >  xmt_byte;    // Transmit output data
       sc_out <sc_biguint<12> > addrb_ioram; // Address for LZW port of IORAM
       sc_out <sc_biguint<12> > outram_cnt;  // Output RAM data count
       sc_out <bool >           web_ioram;   // Write enable for LZW port of IORAM
       sc_out <bool >           enb_ioram;   // Enable LZW port of IORAM
       sc_out <bool >           lzw_done;    // LZW block finished all processing
       sc_out <bool >           done_cr;     // Code value RAM initilization done
  // Inputs
       sc_in <sc_biguint<12> >  char_cnt;    // Number of characters received
       sc_in <sc_biguint<12> >  addra_outram;// Address for port A of out RAM
       sc_in <sc_biguint<8> >   char_in;     // Character in from IORAM
       sc_in <bool >            init_cr;     // Initiliaze code value RAM
       sc_in <bool >            init_lzw;    // Initiliaze the LZW block
       sc_in <bool >            ena_outram;  // Enable for port A of out RAM
       sc_in <bool >            clk;         // System clock
       sc_in <bool >            rst_n;       // System reset, active low
       


  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal <sc_biguint<13> > prefix_data; // Prefix data
  sc_signal <sc_biguint<8> >  append_data; // Append data
  sc_signal <sc_biguint<13> > addr;        // Dictionary RAM address
  sc_signal <sc_biguint<13> > string_data; // String data
  sc_signal <bool >           not_in_mem;  // Address not in code value RAM
  sc_signal <bool >           in_code_mem; // Address in code value RAM
  
  sc_signal <sc_biguint<13> > addrb_cvram; // Address for CV RAM port B
  sc_signal <sc_biguint<13> > wr_cvdataa;  // Write data for code value RAM port A
  sc_signal <sc_biguint<13> > string_reg;  // String register  
  
  sc_signal <sc_biguint<8> >  lzw_byte;    // LZW output data
  sc_signal <sc_biguint<12> > addrb_outram;// Address for out RAM port B
  sc_signal <bool >           wrb_outram;  // Write enable for out RAM port B
  sc_signal <bool >           enb_outram;  // Enable for out RAM port B
                                 
  sc_signal <bool >           done_lzw;    // Done with LZW,early   
  sc_signal <bool >           enb_cvram;   // Enable code value RAM port B 
  sc_signal <bool >           web_cvram;   // Write enable code value RAM port B
  sc_signal <bool >           shift_char;  // Shift character from char. to string reg.  
  sc_signal <bool >           gen_hash;    // Generate hash   
  sc_signal <bool >           recal_hash;  // Recalculate hash  
  sc_signal <bool >           ena_cvram;   // Enable code value RAM port A
  sc_signal <bool >           wea_cvram;   // Write enable code value RAM port A
  sc_signal <bool >           inc_cvadata; // Increment code value RAM port A data
  sc_signal <bool >           wea_acram;   // Write Enable append char RAM port A
  sc_signal <bool >           wea_pcram;   // Write Enable prefix char RAM port A
  sc_signal <bool >           write_data;  // Write data into output register  
  sc_signal <bool >           mux_code_val;// Mux code value into string register
  sc_signal <bool >           tc_outreg;   // Terminal count output register
  sc_signal <bool >           match;       // Match address
  sc_signal <bool >           collis;      // Address collision
  sc_signal <bool >           hash;        // Hash
  sc_signal <bool >           web_outram;  //
  sc_signal <bool >           write_sp;    //
  sc_signal <bool >           valid_dcnt;  //
  sc_signal <bool >           read_data;   //
  sc_signal <bool >           drive0;      // Drive 0
  sc_signal <sc_biguint<8> >  drive0_8bit; // Drive 0 for 8-bits
  sc_signal <sc_biguint<13> > drive1_13bit;// Drive 1 for 13-bits
  sc_signal <sc_biguint<8> >  dummy0;      // Dummy data
  
   dictionary_ram *dictionary_ram1;
   code_value_ram  *code_value_ram1;
   hashl  *hash1;
   lzw_ctrl *lzw_ctrl1;
   outreg  *outreg1;
   io_ram  *outram;
   
  /****************************************************************************
   Instance the synchronizers for the various inputs from switches to
   debounce them.
  ****************************************************************************/
   SC_CTOR(lzw_enc) {
  
   SC_METHOD (combo_lzwencp);	
   //sensitive << rst_n; //uncomment this for sc2v
   
  dictionary_ram1   = new dictionary_ram("dictionary_ram");
  code_value_ram1   = new code_value_ram("code_value_ram");
  hash1             = new hashl("hashl");
  lzw_ctrl1         = new lzw_ctrl("lzw_ctrl");
  outreg1           = new outreg("outreg");
  outram            = new io_ram("io_ram");
  
  /****************************************************************************
   Instance the dictionary RAM
  ****************************************************************************/
    // Outputs
         dictionary_ram1->prefix_data(prefix_data);   // To comparator
         dictionary_ram1->append_data(append_data);   // To comparator
    // Inputs                         
         dictionary_ram1->wea_acram  (wea_acram);     // From lzw_ctrl 
         dictionary_ram1->wea_pcram  (wea_pcram);     // From lzw_ctrl   
         dictionary_ram1->addr       (addr);          // From    
         dictionary_ram1->char_data  (char_in);       // From 
         dictionary_ram1->string_data(string_reg);    // From 
         dictionary_ram1->clk        (clk);           // From iopads
         dictionary_ram1->rst_n      (rst_n);         // From iopads
 
  /****************************************************************************
   Instance the code value RAM
  ****************************************************************************/ 
    // Outputs
         code_value_ram1->rd_dataa  (string_data);   // To cmp
    // Inputs		                    
         code_value_ram1->wr_porta  (wea_cvram);     // From lzw_ctrl
         code_value_ram1->en_porta  (ena_cvram);     // From lzw_ctrl
         code_value_ram1->addra     (addr);          // From 
         code_value_ram1->wr_dataa  (wr_cvdataa);    // From lzw_ctrl
         code_value_ram1->wr_portb  (web_cvram);     // From lzw_ctrl
         code_value_ram1->en_portb  (enb_cvram);     // From lzw_ctrl
         code_value_ram1->addrb     (addrb_cvram);   // From lzw_ctrl
         code_value_ram1->wr_datab  (drive1_13bit);  // From 
         code_value_ram1->clk       (clk);	         // From iopads
         code_value_ram1->rst_n     (rst_n);         // From iopads

  /****************************************************************************
   Instance the hash block
  ****************************************************************************/  
    // Outputs
         hash1->addr         (addr);          // To dictionary
         hash1->string_reg   (string_reg);    // To dictionary
         hash1->not_in_mem   (not_in_mem);    // To lzw_ctrl
         hash1->match        (match);         // To lzw_ctrl
         hash1->collis       (collis);        // To lzw_ctrl
         hash1->in_code_mem  (in_code_mem);   // To lzw_ctrl
    // Inputs
         hash1->gen_hash     (gen_hash);      // From lzw_ctrl
         hash1->recal_hash   (recal_hash);    // From lzw_ctrl
         hash1->shift_char   (shift_char);    // From lzw_ctrl
         hash1->mux_code_val (mux_code_val);  // From lzw_ctrl
         hash1->char_in      (char_in);       // From io_ram
         hash1->string_data  (string_data);   // From code_value_ram
         hash1->append_data  (append_data);   // From dictionary
         hash1->prefix_data  (prefix_data);   // From dictionary
         hash1->clk          (clk);           // From iopads
         hash1->rst_n        (rst_n);         // From iopads

  /****************************************************************************
   Instance the control block
  ****************************************************************************/ 
    // Outputs
         lzw_ctrl1->done_cr      (done_cr);     // To top_ctrl
         lzw_ctrl1->lzw_done     (lzw_done);    // To top_ctrl 
         lzw_ctrl1->gen_hash     (gen_hash);    // To hash
         lzw_ctrl1->recal_hash   (recal_hash);  // To hash
         lzw_ctrl1->addrb_ioram  (addrb_ioram); // To IO RAM
         lzw_ctrl1->enb_ioram    (enb_ioram);   // To IO RAM
         lzw_ctrl1->web_ioram    (web_ioram);   // To IO RAM     
         lzw_ctrl1->addrb_outram (addrb_outram);// To out RAM
         lzw_ctrl1->enb_outram   (enb_outram);  // To out RAM
         lzw_ctrl1->web_outram   (web_outram);  // To out RAM       
         lzw_ctrl1->addrb_cvram  (addrb_cvram); // To code_value_ram
         lzw_ctrl1->enb_cvram    (enb_cvram);   // To code_value_ram
         lzw_ctrl1->web_cvram    (web_cvram);   // To code_value_ram
         lzw_ctrl1->wr_cvdataa   (wr_cvdataa);  // To code_value_ram
         lzw_ctrl1->ena_cvram    (ena_cvram);   // To code_value_ram
         lzw_ctrl1->wea_cvram    (wea_cvram);   // To code_value_ram
         lzw_ctrl1->wea_acram    (wea_acram);   // To dictionary_ram
         lzw_ctrl1->wea_pcram    (wea_pcram);   // To dictionary_ram  
         lzw_ctrl1->write_data   (write_data);  // To outreg
         lzw_ctrl1->read_data    (read_data);   // To outreg
         lzw_ctrl1->write_sp     (write_sp);    // To outreg
         lzw_ctrl1->shift_char   (shift_char);  // To hash
         lzw_ctrl1->mux_code_val (mux_code_val);// To hash
         lzw_ctrl1->outram_cnt   (outram_cnt);  // To top_ctrl
    // Inputs                    
         lzw_ctrl1->valid_dcnt   (valid_dcnt);  // From outreg  
         lzw_ctrl1->tc_outreg    (tc_outreg);   // From outreg 
         lzw_ctrl1->init_cr      (init_cr);     // From top_ctrl       
         lzw_ctrl1->init_lzw     (init_lzw);    // From top_ctrl   
         lzw_ctrl1->char_cnt     (char_cnt);    // From top_ctrl
         lzw_ctrl1->not_in_mem   (not_in_mem);  // From hash
         lzw_ctrl1->match        (match);       // From hash
         lzw_ctrl1->collis       (collis);      // From hash
         lzw_ctrl1->in_code_mem  (in_code_mem); // To lzw_ctrl
         lzw_ctrl1->clk          (clk);         // From iopads
         lzw_ctrl1->rst_n        (rst_n);       // From iopads

  /****************************************************************************
   Instance the output forming block
  ****************************************************************************/ 
    // Outputs
         outreg1->valid_dcnt  (valid_dcnt);  // To lzw_ctrl  
         outreg1->tc_outreg   (tc_outreg);   // To lzw_ctrl 
         outreg1->lzw_byte    (lzw_byte);    // To IO RAM
    // Inputs                 
         outreg1->write_data  (write_data);  // From lzw_ctrl
         outreg1->write_sp    (write_sp);    // From lzw_ctrl
         outreg1->read_data   (read_data);   // From lzw_ctrl
         outreg1->prefix_data (prefix_data); // From lzw_ctrl
         outreg1->clk         (clk);         // From iopads
         outreg1->rst_n       (rst_n);       // From iopads
   
  /****************************************************************************
   Instance the output RAM
  ****************************************************************************/ 
    // Outputs
         outram->rd_dataa (xmt_byte);        // To ser
         outram->rd_datab (dummy0);          // To lzw_enc
    // Inputs                         
         outram->wr_porta (drive0);          // From     
         outram->en_porta (ena_outram);      // From top_ctrl
         outram->addra    (addra_outram);    // From top_ctrl
         outram->wr_dataa (drive0_8bit);     // From ser
         outram->wr_portb (web_outram);      // From lzw_enc
         outram->en_portb (enb_outram);      // From lzw_enc
         outram->addrb    (addrb_outram);    // From lzw_enc        
         outram->wr_datab (lzw_byte);        // From lzw_enc
         outram->clk      (clk);             // From iopads
         outram->rst_n    (rst_n);           // From iopads
   }
  
  void combo_lzwencp ();
  };      
