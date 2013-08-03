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
// Description: Dual Port SRAM. Equivelant to Xilinx RAM 
//
//*****************************************************************************

  #include "systemc.h"

  /****************************************************************************
   Single Port synchronous RAM 512x8
  ****************************************************************************/

  SC_MODULE(RAMB4_S8) {
  sc_in  <bool >                   CLK;    // Clock
  sc_in  <bool >                   RST;    // Reset, active high     
  sc_in  <bool >                   EN;     // Enable       
  sc_in  <bool >                   WE;     // Write enable       
  sc_in  <sc_uint<9> >             ADDR;   // Address        
  sc_in  <sc_biguint<8> >          DI;     // Data in       
  sc_out <sc_biguint<8> >          DO;     // Data out

  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal<sc_biguint <8> > mem [512];


   SC_CTOR(RAMB4_S8) {
    SC_METHOD (read_memp);
      sensitive_pos << CLK;
    SC_METHOD (write_memp);
      sensitive_pos << CLK;
  }
  
  void read_memp();
  void write_memp();
  
  };
