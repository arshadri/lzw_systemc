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
// Description: Hash generator.
//
//*****************************************************************************

  #include "systemc.h"
  /****************************************************************************
   Hash generation
  ****************************************************************************/
  SC_MODULE(hashl) {
  // Outputs
       sc_out <sc_biguint<13> > addr;         // To different RAM's
       sc_out <sc_biguint<13> > string_reg;   // To prefix RAM
       sc_out <bool >           not_in_mem;   // To lzw_ctrl
       sc_out <bool >           match;        // To lzw_ctrl
       sc_out <bool >           collis;       // To lzw_ctrl
       sc_out <bool >           in_code_mem;  // To lzw_ctrl
  // Inputs
       sc_in <sc_biguint<8> >   char_in;      // From io_ram 
       sc_in <sc_biguint<13> >  string_data;  // From code_value_ram
       sc_in <sc_biguint<8> >   append_data;  // From dictionary_ram 
       sc_in <sc_biguint<13> >  prefix_data;  // From dictionary_ram 
       sc_in <bool >            gen_hash;     // From lzw_ctrl
       sc_in <bool >            recal_hash;   // From lzw_ctrl
       sc_in <bool >            shift_char;   // From lzw_ctrl
       sc_in <bool >            mux_code_val; // From lzw_ctrl
       sc_in <bool >            clk;          // From iopads
       sc_in <bool >            rst_n;        // From iopads
       
 
  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal <sc_biguint<13> > addr_save;    // Save currently generated address 
  sc_signal <bool >        gen_hash_s;      // Generate hash delayed
  sc_signal <bool >        gen_hash_ss;     // Generate hash delayed by 2

  sc_signal <sc_biguint<13> > index;        // Index
  sc_signal <bool >        cmp_append_char; // Compare append character
  sc_signal <bool >        cmp_prefix_data; // Compare prefix data
  sc_signal <sc_uint<12> > addr_saves;   // Save currently generated address 
  
  /****************************************************************************
   Logic to determine if the current character is a hit in the dictionary
  ****************************************************************************/ 
  SC_CTOR (hashl) {
		SC_METHOD (hashl_combo);		
		sensitive << string_data << gen_hash_ss << append_data << char_in << prefix_data << string_reg;
		SC_METHOD (in_code_memp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (matchp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (collisp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (genhashp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (genhashssp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (addrsavep);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (indexp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (stringregp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (recalhashp);
		sensitive << recal_hash << addr_saves << index;
		SC_METHOD (addrp);
		sensitive << addr_save;
  }
  void hashl_combo ();		
  void in_code_memp ();
  void matchp ();
  void collisp ();
  void genhashp ();
  void genhashssp ();
  void addrsavep ();
  void indexp ();
  void recalhashp ();
  void stringregp ();
  void addrp ();
};
