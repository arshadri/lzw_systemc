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
  #include "RAMB16_S18_S18.h"
 
  /****************************************************************************
   Logic for memory
  ****************************************************************************/ 
  
  // Memory Write Block for port A
  // Write Operation : When WE = 1, EN = 1
  void RAMB16_S18_S18::write_memp_A () {
  sc_uint <9> addra_int = ADDRA.read(); // tmp - Visual C++ compile correctly wihti this junk line
    if (CLKA.read() & ENA.read() & WEA.read()) {
      mem[ADDRA.read()] = DIA.read();
    }
    else if (CLKB.read() & ENB.read() & WEB.read()) {
      mem[ADDRB.read()] = DIB.read();
    }
  }

  // Memory Read Block for port A
  // Read Operation : When EN = 1
  void RAMB16_S18_S18::read_memp_A () {
    if (ENA.read())  {
      DOA.write(mem[ADDRA.read()]);
    }
  }
  

  // Memory Read Block for port B
  // Read Operation : When EN = 1
  void RAMB16_S18_S18::read_memp_B () {
    if (ENB.read())  {
      DOB.write(mem[ADDRB.read()]);
    }
  }
  
