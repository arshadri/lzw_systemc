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
// Description: Clock and reset generator.
//
//*****************************************************************************

  #include "systemc.h"
  /****************************************************************************
   Generate 33MHZ clock, and synchronize the reset, and generate fixed output
  ****************************************************************************/
  SC_MODULE(clk_rst) { 
  	
    sc_out <bool > clk;                // Clock 33 MHZ used everywhere
    sc_out <bool > rst_n;              // Synchronized reset, active low
    sc_out <bool > drive0;             // Drive 0
    sc_out <sc_biguint<8> > drive0_8bit;  // Drive 0 for 8-bits

    sc_in  <bool > clk66;              // system clock, 66mhz
    sc_in  <bool > rst;                // System reset, active high 
    
  /****************************************************************************
   Internal declarations
  ****************************************************************************/      
    sc_signal <bool >    rst_s;         // First Synchronized reset

    SC_CTOR (clk_rst) {
		  SC_METHOD (combop);
		  sensitive << rst_s;		
		  SC_METHOD (rstp);
		  sensitive_pos << clk;
		  sensitive_pos << rst;
		  SC_METHOD (clkp);
		  sensitive_pos << clk66;	
    }
  void combop ();
  void rstp ();
  void clkp ();
  
  };
