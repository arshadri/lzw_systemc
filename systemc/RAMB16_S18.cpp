
  #include "RAMB16_S18.h"
 
  /****************************************************************************
   Logic for memory
  ****************************************************************************/ 
  
  // Memory Write Block 
  // Write Operation : When we = 1, en = 1
  void RAMB16_S18::write_memp () {
  sc_uint <9> addra_int = ADDR.read(); // tmp - Visual C++ compile correctly wihti this junk line
    if (EN.read() & WE.read()) {
      mem[ADDR.read()] = DI.read();
    }
  }

  // Memory Read Block 
  // Read Operation : When EN = 1
  void RAMB16_S18::read_memp () {
    if (EN.read())  {
      DO.write(mem[ADDR.read()]);
    }
  }
