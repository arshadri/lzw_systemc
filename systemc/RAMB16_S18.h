

  #include "systemc.h"
  //#define DATA_WIDTH        16 
  //#define ADDR_WIDTH        10 
  //#define RAM_DEPTH         1 << ADDR_WIDTH

  /****************************************************************************
   Single Port synchronous RAM 1024x16
  ****************************************************************************/

  SC_MODULE (RAMB16_S18) {
  sc_in  <bool >                   CLK;    // Clock
  sc_in  <bool >                   SSR;    // Reset, active high     
  sc_in  <bool >                   EN;     // Enable       
  sc_in  <bool >                   WE;     // Write enable       
  sc_in  <sc_uint<10> >            ADDR;   // Address        
  sc_in  <sc_biguint<16> >         DI;     // Data in         
  sc_in  <sc_uint<2> >             DIP;    // Data in parity      
  sc_out <sc_biguint<16> >         DO;     // Data out    
  sc_out <sc_uint<2> >             DOP;    // Data out parity

  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal<sc_biguint <16> > mem [1024];


   SC_CTOR(RAMB16_S18) {
    SC_METHOD (read_memp);
      sensitive_pos << CLK;
    SC_METHOD (write_memp);
      sensitive_pos << CLK;
  }
  
  void read_memp();
  void write_memp();
  
  };
