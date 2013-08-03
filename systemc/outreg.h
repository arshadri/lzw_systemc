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
// Description: Shift register for combining and outputting LZW encoded 
//              data to IORAM 
//
//*****************************************************************************
    #include "systemc.h"
  /****************************************************************************
   Output forming logic.
  ****************************************************************************/

  SC_MODULE(outreg) {
  // Outputs
       sc_out <sc_biguint<8> > lzw_byte;      // Write data for IO RAM port B
       sc_out <bool >          valid_dcnt;    // Data count is a valid count
       sc_out <bool >          tc_outreg;     // Terminal count output register
  // Inputs
       sc_in <sc_biguint<13> >  prefix_data;  // Prefix data
       sc_in <bool >            write_data;   // Write data into output register
       sc_in <bool >            write_sp;     // Write special code into output register
       sc_in <bool >            read_data;    // Read data from output register 
       sc_in <bool >            clk;          // From iopads
       sc_in <bool >            rst_n;        // From iopads
       

  /****************************************************************************
   Internal declarations
  ****************************************************************************/   
  sc_signal <bool > flush;                    // Flush the output register
  
  sc_signal <sc_biguint<5> > datain_cnt;      // Input data count
  sc_signal <sc_biguint<32> > shift_reg;      // Shift register
  

  SC_CTOR (outreg) {
		SC_METHOD (outreg_combop);		
		sensitive << read_data << datain_cnt << shift_reg;
		SC_METHOD (shift_regp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (datain_cntp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
  }
  
  void shift_regp ();	
  void datain_cntp ();
  void outreg_combop ();

 
  };
