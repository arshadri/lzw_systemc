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
// Description: Dictionary RAM.
//
//*****************************************************************************

  #include "systemc.h" 
  #include "prefix_code_ram.cpp" 
  #include "append_char_ram.cpp"
  /****************************************************************************
   Dictionary RAM.
  ****************************************************************************/
  SC_MODULE(dictionary_ram) {
  // Outputs
       sc_out <sc_biguint<13> > prefix_data;  // Prefix data
       sc_out <sc_biguint<8> >  append_data;  // Append data
  // Inputs
       sc_in <sc_biguint<8> >   char_data;    // Character data
       sc_in <sc_biguint<13> >  addr;         // Address
       sc_in <sc_biguint<13> >  string_data;  // String data
       sc_in <bool >            wea_acram;    // Write Enable append char RAM port A 
       sc_in <bool >            wea_pcram;    // Write Enable prefix code char RAM port A
       sc_in <bool >            clk;          // From iopads
       sc_in <bool >            rst_n;        // From iopads
  
  /****************************************************************************
   Internal declarations
  ****************************************************************************/   
  sc_signal <bool >           drive_1;         // Drive 1
  sc_signal <sc_biguint<12> > raddr;
 
   prefix_code_ram *prefix_code_ram1;
   append_char_ram *append_char_ram1;
   
    SC_CTOR(dictionary_ram) {
  
    SC_METHOD(combo_dictp);
    sensitive << addr;
    
  prefix_code_ram1   = new prefix_code_ram("prefix_code_ram");
  append_char_ram1   = new append_char_ram("append_char_ram");
  
  /****************************************************************************
   Instance the prefix code RAM
  ****************************************************************************/
    // Outputs
         prefix_code_ram1->rd_data     (prefix_data);
    // Inputs
         prefix_code_ram1->wren        (wea_pcram);
         prefix_code_ram1->en          (drive_1);
         prefix_code_ram1->addr        (raddr);
         prefix_code_ram1->wr_data     (string_data);
         prefix_code_ram1->clk         (clk); 
         prefix_code_ram1->rst_n       (rst_n);
  
  /****************************************************************************
   Instance the append character RAM
  ****************************************************************************/
    // Outputs
         append_char_ram1->rd_data     (append_data);
    // Inputs
         append_char_ram1->wren        (wea_acram);
         append_char_ram1->en          (drive_1);
         append_char_ram1->addr        (raddr);
         append_char_ram1->wr_data     (char_data);
         append_char_ram1->clk         (clk); 
         append_char_ram1->rst_n       (rst_n);
  
  }

  void combo_dictp ();
  };  
