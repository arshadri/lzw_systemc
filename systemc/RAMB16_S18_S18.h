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
   Dual Port synchronous RAM 512x8
  ****************************************************************************/

SC_MODULE (RAMB16_S18_S18) {
  sc_in  <bool >                   CLKA;   // Clock, port A
  sc_in  <bool >                   SSRA;   // Reset, port A, active high     
  sc_in  <bool >                   ENA;    // Enable, port A      
  sc_in  <bool >                   WEA;    // Write enable, port A       
  sc_in  <sc_uint<10> >            ADDRA;  // Address, port A        
  sc_in  <sc_biguint<16> >         DIA;    // Data in, port A  
  sc_in  <bool >                   CLKB;   // Clock, port B
  sc_in  <bool >                   SSRB;   // Reset, port B, active high     
  sc_in  <bool >                   ENB;    // Enable, port B      
  sc_in  <bool >                   WEB;    // Write enable, port B       
  sc_in  <sc_uint<10> >            ADDRB;  // Address, port B        
  sc_in  <sc_biguint<16> >         DIB;    // Data in, port B           
  sc_out <sc_biguint<16> >         DOA;    // Data out, port A 
  sc_out <sc_biguint<16> >         DOB;    // Data out, port B

  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal<sc_biguint <16> > mem [1024];


   SC_CTOR(RAMB16_S18_S18) {
    SC_METHOD (read_memp_A);
      sensitive_pos << CLKA;
    SC_METHOD (write_memp_A);
      sensitive_pos << CLKA;
      sensitive_pos << CLKB;
    SC_METHOD (read_memp_B);
      sensitive_pos << CLKB;
  }
  
  void read_memp_A();
  void write_memp_A();
  void read_memp_B();
  };
