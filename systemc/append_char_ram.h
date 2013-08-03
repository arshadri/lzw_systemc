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
// Description:  Append Character RAM.
//
//*****************************************************************************

  #include "systemc.h"
  #include "RAMB4_S8.cpp"
  /****************************************************************************
   Append character RAM.
  ****************************************************************************/
  
  SC_MODULE(append_char_ram) {
  // Outputs
       sc_out <sc_biguint<8> >  rd_data;    // Read data from RAM
  // Inputs
       sc_in <sc_biguint<12> > addr;        // RAM address
       sc_in <sc_biguint<8> >  wr_data;     // Write data
       sc_in <bool >           wren;        // Write enable RAM
       sc_in <bool >           en;          // RAM enable
       sc_in <bool >           clk;         // System clock
       sc_in <bool >           rst_n;       // System reset, active low

  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal <sc_biguint<8> > rd_data_r; // Registered read data
  
  sc_signal <sc_biguint<8> > rd_data0;  // Read data RAM 0
  sc_signal <sc_biguint<8> > rd_data1;  // Read data RAM 1
  sc_signal <sc_biguint<8> > rd_data2;  // Read data RAM 2
  sc_signal <sc_biguint<8> > rd_data3;  // Read data RAM 3
  sc_signal <sc_biguint<8> > rd_data4;  // Read data RAM 4
  sc_signal <sc_biguint<8> > rd_data5;  // Read data RAM 5
  sc_signal <sc_biguint<8> > rd_data6;  // Read data RAM 6
  sc_signal <sc_biguint<8> > rd_data7;  // Read data RAM 7
  sc_signal <bool > ram_en0;            // Enable for RAM 0
  sc_signal <bool > ram_en1;            // Enable for RAM 1 
  sc_signal <bool > ram_en2;            // Enable for RAM 2 
  sc_signal <bool > ram_en3;            // Enable for RAM 3 
  sc_signal <bool > ram_en4;            // Enable for RAM 4 
  sc_signal <bool > ram_en5;            // Enable for RAM 5 
  sc_signal <bool > ram_en6;            // Enable for RAM 6 
  sc_signal <bool > ram_en7;            // Enable for RAM 7  
  sc_signal <bool > en_porta_r;         // Registered enable
  sc_signal <bool > rst;                // Reset inverted version of input  
  sc_signal <sc_uint<9> >  raddr;

  
  

  RAMB4_S8 *i0, *i1, *i2, *i3, *i4, *i5, *i6, *i7;
  
  /****************************************************************************
   Generate the enable signals for the RAM's and the output data muxing
  ****************************************************************************/
 
  SC_CTOR (append_char_ram) {
		SC_METHOD (append_char_ram_combop);		
		sensitive << addr << en << rst_n;	
		SC_METHOD (append_char_ram_readp);
		sensitive << en_porta_r << addr << rd_data_r << rd_data0 << rd_data1 << rd_data2 << rd_data3 << rd_data4 << rd_data5 << rd_data6 << rd_data7;
		SC_METHOD (rd_data_rp);
		sensitive_pos << clk;
		sensitive_neg << rst_n;
		SC_METHOD (en_portap);
		sensitive_pos << clk;
	  sensitive_neg << rst_n;
		
    i0 = new RAMB4_S8("i0");
    i1 = new RAMB4_S8("i1");
    i2 = new RAMB4_S8("i2");
    i3 = new RAMB4_S8("i3");
    i4 = new RAMB4_S8("i4");
    i5 = new RAMB4_S8("i5");
    i6 = new RAMB4_S8("i6");
    i7 = new RAMB4_S8("i7");
  /****************************************************************************
   Instance the RAMS
  ****************************************************************************/
    // Outputs
         i0->DO        (rd_data0);
    // Inputs
         i0->ADDR      (raddr);         
         i0->CLK       (clk);        
         i0->DI        (wr_data);   
         i0->EN        (ram_en0);
         i0->WE        (wren);
         i0->RST       (rst);
  
    // Outputs
         i1->DO        (rd_data1);
    // Inputs
         i1->ADDR      (raddr);         
         i1->CLK       (clk);        
         i1->DI        (wr_data);   
         i1->EN        (ram_en1);
         i1->WE        (wren);
         i1->RST       (rst);

    // Outputs
         i2->DO        (rd_data2);
    // Inputs
         i2->ADDR      (raddr);         
         i2->CLK       (clk);        
         i2->DI        (wr_data);   
         i2->EN        (ram_en2);
         i2->WE        (wren);
         i2->RST       (rst);

    // Outputs
         i3->DO        (rd_data3);
    // Inputs
         i3->ADDR      (raddr);         
         i3->CLK       (clk);        
         i3->DI        (wr_data);   
         i3->EN        (ram_en3);
         i3->WE        (wren);
         i3->RST       (rst);

    // Outputs
         i4->DO        (rd_data4);
    // Inputs
         i4->ADDR      (raddr);         
         i4->CLK       (clk);        
         i4->DI        (wr_data);   
         i4->EN        (ram_en4);
         i4->WE        (wren);
         i4->RST       (rst);

    // Outputs
         i5->DO        (rd_data5);
    // Inputs
         i5->ADDR      (raddr);         
         i5->CLK       (clk);        
         i5->DI        (wr_data);   
         i5->EN        (ram_en5);
         i5->WE        (wren);
         i5->RST       (rst);

    // Outputs
         i6->DO        (rd_data6);
    // Inputs
         i6->ADDR      (raddr);         
         i6->CLK       (clk);        
         i6->DI        (wr_data);   
         i6->EN        (ram_en6);
         i6->WE        (wren);
         i6->RST       (rst);
  
    // Outputs
         i7->DO        (rd_data7);
    // Inputs
         i7->ADDR      (raddr);         
         i7->CLK       (clk);        
         i7->DI        (wr_data);   
         i7->EN        (ram_en7);
         i7->WE        (wren);
         i7->RST       (rst);

  }
  void rd_data_rp ();
  void en_portap  ();
  void append_char_ram_readp(); 
  void append_char_ram_combop(); 
  
};
 
