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
// Description: Prefix Code RAM 
//
//*****************************************************************************
  #include "systemc.h"
  #include "RAMB16_S18.cpp"
  
  /****************************************************************************
   Prefix Code RAM.
  ****************************************************************************/
  SC_MODULE(prefix_code_ram) {
  // Outputs
       sc_out <sc_biguint<13> > rd_data;     // Read data from RAM
  // Inputs
       sc_in <sc_biguint<12> > addr;         // RAM address
       sc_in <sc_biguint<13> > wr_data;      // Write data
       sc_in <bool >           wren;         // Write enable RAM
       sc_in <bool >           en;           // RAM enable
       sc_in <bool >           clk;          // System clock
       sc_in <bool >           rst_n;        // System reset, active low
   
  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal <sc_biguint<13> > rd_data_r;     // Registered read data
  sc_signal <sc_biguint<16> > rd_data0;      // Read data RAM 0
  sc_signal <sc_biguint<16> > rd_data1;      // Read data RAM 1
  sc_signal <sc_biguint<16> > rd_data2;      // Read data RAM 2
  sc_signal <sc_biguint<16> > rd_data3;      // Read data RAM 3
  sc_signal <bool >           ram_en0;       // Enable for RAM 0  
  sc_signal <bool >           ram_en1;       // Enable for RAM 1 
  sc_signal <bool >           ram_en2;       // Enable for RAM 2 
  sc_signal <bool >           ram_en3;       // Enable for RAM 3 
  
  sc_signal <bool >           en_porta_r;     // Registered enable   
  sc_signal <bool >           rst;            // Reset inverted version of input
  sc_signal <sc_uint<10> >    raddr;
  sc_signal <sc_uint<2> >     drive0_2;
  sc_signal <sc_biguint<3> >  drive0_3;
  sc_signal <sc_uint<2> >     dummy0, dummy1, dummy2, dummy3;
  sc_signal <sc_biguint<16> > wrdatac;
  
    RAMB16_S18 *i0, *i1, *i2, *i3;

   SC_CTOR (prefix_code_ram) {
        SC_METHOD (prefix_code_ram_combop);              
        sensitive << addr << en << rst_n << wr_data;       
        SC_METHOD (prefix_code_ram_readp);
        sensitive << en_porta_r << addr << rd_data_r << rd_data0 << rd_data1 << rd_data2 << rd_data3;
        SC_METHOD (en_portap);
        sensitive_pos << clk;
        sensitive_neg << rst_n;
        SC_METHOD (rd_data_rp);
        sensitive_pos << clk;
        sensitive_neg << rst_n;
        
  /****************************************************************************
   Instance the RAMS
  ****************************************************************************/
    i0 = new RAMB16_S18("i0");
    i1 = new RAMB16_S18("i1");
    i2 = new RAMB16_S18("i2");
    i3 = new RAMB16_S18("i3");
    
    // Outputs
         i0->DO        (rd_data0);
         i0->DOP       (dummy0);
    // Inputs
         i0->ADDR      (raddr);        
         i0->CLK       (clk);        
         i0->DI        (wrdatac);     
         i0->DIP       (drive0_2);  
         i0->EN        (ram_en0);
         i0->WE        (wren);
         i0->SSR       (rst);

    // Outputs
         i1->DO        (rd_data1);
         i1->DOP       (dummy1);
    // Inputs
         i1->ADDR      (raddr);         
         i1->CLK       (clk);        
         i1->DI        (wrdatac);     
         i1->DIP       (drive0_2);  
         i1->EN        (ram_en1);
         i1->WE        (wren);
         i1->SSR       (rst);
 
    // Outputs
         i2->DO        (rd_data2);
         i2->DOP       (dummy2);
    // Inputs
         i2->ADDR      (raddr);         
         i2->CLK       (clk);        
         i2->DI        (wrdatac);     
         i2->DIP       (drive0_2);  
         i2->EN        (ram_en2);
         i2->WE        (wren);
         i2->SSR       (rst);
 
    // Outputs
         i3->DO        (rd_data3);
         i3->DOP       (dummy3);
    // Inputs
         i3->ADDR      (raddr);         
         i3->CLK       (clk);        
         i3->DI        (wrdatac);     
         i3->DIP       (drive0_2);  
         i3->EN        (ram_en3);
         i3->WE        (wren);
         i3->SSR       (rst);
         
    }
  void prefix_code_ram_combop ();                   
  void prefix_code_ram_readp ();
  void en_portap ();
  void rd_data_rp ();
  };
 
