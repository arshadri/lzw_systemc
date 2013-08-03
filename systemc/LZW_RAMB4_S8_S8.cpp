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
// Description: Dual Port synchronous RAM 512x8.
//
//*****************************************************************************

  #include "LZW_RAMB4_S8_S8.h"
 
  /****************************************************************************
   Logic for memory
  ****************************************************************************/ 
  
  // Memory Write Block for port A
  // Write Operation : When WE = 1, EN = 1
  void LZW_RAMB4_S8_S8::write_memp_A () {
    sc_uint <9> addra_int = ADDRA.read(); // tmp - Visual C++ compile correctly wiht this junk line
    if (ENA.read() & WEA.read()) {
      mem[ADDRA.read()] = DIA.read();
    }
  }

  // Memory Read Block for port A
  // Read Operation : When EN = 1
  void LZW_RAMB4_S8_S8::read_memp_A () {
    if (ENA.read())  {
      DOA.write(mem[ADDRA.read()]);
    }
  }
  
  // Memory Write Block for port B
  // Write Operation : When WE = 1, EN = 1
  void LZW_RAMB4_S8_S8::write_memp_B () {
    if (ENB.read() & WEB.read()) {
      mem[ADDRB.read()] = DIB.read();
    }
  }

  // Memory Read Block for port B
  // Read Operation : When EN = 1
  void LZW_RAMB4_S8_S8::read_memp_B () {
    if (ENB.read())  {
      DOB.write(mem[ADDRB.read()]);
    }
  }
  
