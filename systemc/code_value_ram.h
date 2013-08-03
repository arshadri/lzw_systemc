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
// Description: Code value RAM.
//
//*****************************************************************************

  #include "systemc.h"
  #include "RAMB16_S18_S18.cpp"
  
  /****************************************************************************
   Code Value RAM.
   One port of the RAM is connected to the initilization logic
   Second port of the RAM is used for string data
  ****************************************************************************/
  SC_MODULE(code_value_ram) {
  // Outputs
       sc_out <sc_biguint<13> > rd_dataa;   // Read data for port A
  // Inputs  
       sc_in  <sc_biguint<13> > addra;      // RAM address for port A
       sc_in  <sc_biguint<13> > addrb;      // RAM address for port B
       sc_in  <sc_biguint<13> > wr_dataa;   // Write data for port A
       sc_in  <sc_biguint<13> > wr_datab;   // Write data for port B
       sc_in  <bool >           wr_porta;   // Write enable for port A
       sc_in  <bool >           en_porta;   // RAM enable for port A
       sc_in  <bool >           wr_portb;   // Write enable for port B
       sc_in  <bool >           en_portb;   // RAM enable for port B
       sc_in  <bool >           clk;        // System clock
       sc_in  <bool >           rst_n;      // System reset, active low

  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal <sc_biguint<13> > rd_dataa_r;   // Registered read data for port A  
  sc_signal <sc_biguint<16> > rd_dataa0;    // Read data port A RAM 0
  sc_signal <sc_biguint<16> > rd_dataa1;    // Read data port A RAM 1
  sc_signal <sc_biguint<16> > rd_dataa2;    // Read data port A RAM 2
  sc_signal <sc_biguint<16> > rd_dataa3;    // Read data port A RAM 3
  sc_signal <bool >           en_porta_r;   // Registered enable for port A
  sc_signal <bool >           en_a0;        // Enable for port A of RAM 0 
  sc_signal <bool >           en_a1;        // Enable for port A of RAM 1 
  sc_signal <bool >           en_a2;        // Enable for port A of RAM 2 
  sc_signal <bool >           en_a3;        // Enable for port A of RAM 3 
  sc_signal <bool >           rst;          // Reset inverted version of input
  sc_signal <sc_uint<10> >    raddra;
  sc_signal <sc_uint<10> >    raddrb;
  sc_signal <sc_biguint<3> >  drive0_3;
  sc_signal <sc_biguint<16> > ddummy0, ddummy1, ddummy2, ddummy3;  
  sc_signal <sc_biguint<16> > wr_dataac, wr_databc;

    RAMB16_S18_S18 *i0, *i1, *i2, *i3;
 
   SC_CTOR (code_value_ram) {
        SC_METHOD (code_value_ram_combop);              
        sensitive << addra << addrb << en_porta << rst_n << wr_dataa << wr_datab;       
        SC_METHOD (code_value_ram_readap);
        sensitive << en_porta_r << addra << rd_dataa_r << rd_dataa0 << rd_dataa1 << rd_dataa2 << rd_dataa3;
        SC_METHOD (en_portap);
        sensitive_pos << clk;
        sensitive_neg << rst_n;
        SC_METHOD (rd_dataa_rp);
        sensitive_pos << clk;
        sensitive_neg << rst_n;
  /****************************************************************************
   Instance the RAMS
  ****************************************************************************/
    i0 = new RAMB16_S18_S18("i0");
    i1 = new RAMB16_S18_S18("i1");
    i2 = new RAMB16_S18_S18("i2");
    i3 = new RAMB16_S18_S18("i3");    
    
    // Outputs
         i0->DOA       (rd_dataa0);
         i0->DOB       (ddummy0);
    // Inputs
         i0->ADDRA     (raddra);         
         i0->CLKA      (clk);        
         i0->DIA       (wr_dataac); 
         i0->ENA       (en_a0);
         i0->WEA       (wr_porta);
         i0->SSRA      (rst);
         i0->ADDRB     (raddrb);         
         i0->CLKB      (clk);        
         i0->DIB       (wr_databc);  
         i0->ENB       (en_portb);
         i0->WEB       (wr_portb);
         i0->SSRB      (rst);
 
    // Outputs
         i1->DOA       (rd_dataa1);
         i1->DOB       (ddummy1);
    // Inputs
         i1->ADDRA     (raddra);                   
         i1->CLKA      (clk);                  
         i1->DIA       (wr_dataac);             
         i1->ENA       (en_a1);          
         i1->WEA       (wr_porta);             
         i1->SSRA      (rst);                  
         i1->ADDRB     (raddrb);                   
         i1->CLKB      (clk);                  
         i1->DIB       (wr_databc);             
         i1->ENB       (en_portb);          
         i1->WEB       (wr_portb);             
         i1->SSRB      (rst);                   
 
    // Outputs
         i2->DOA       (rd_dataa2);
         i2->DOB       (ddummy2);
    // Inputs
         i2->ADDRA     (raddra);                   
         i2->CLKA      (clk);                  
         i2->DIA       (wr_dataac);              
         i2->ENA       (en_a2);          
         i2->WEA       (wr_porta);             
         i2->SSRA      (rst);                  
         i2->ADDRB     (raddrb);                   
         i2->CLKB      (clk);                  
         i2->DIB       (wr_databc);              
         i2->ENB       (en_portb);          
         i2->WEB       (wr_portb);             
         i2->SSRB      (rst);                   
  

    // Outputs
         i3->DOA       (rd_dataa3);
         i3->DOB       (ddummy3);
    // Inputs
         i3->ADDRA     (raddra);                  
         i3->CLKA      (clk);                  
         i3->DIA       (wr_dataac);              
         i3->ENA       (en_a3);          
         i3->WEA       (wr_porta);             
         i3->SSRA      (rst);                  
         i3->ADDRB     (raddrb);                  
         i3->CLKB      (clk);                  
         i3->DIB       (wr_databc);              
         i3->ENB       (en_portb);          
         i3->WEB       (wr_portb);             
         i3->SSRB      (rst);                   
  
    }

  void code_value_ram_combop () ;
  void code_value_ram_readap () ;  
  void en_portap () ;
  void rd_dataa_rp () ;

  };
