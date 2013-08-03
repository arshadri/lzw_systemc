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
// Description: Input/Output RAM.
//
//*****************************************************************************

  #include "systemc.h"
  #include "RAMB4_S8_S8.cpp"
  
  /****************************************************************************
   Input output RAM.
   One port of the RAM is connected to the serial port
   Second port of the RAM is connected to the output forming logic of the
   LZW block
  ****************************************************************************/
  SC_MODULE(io_ram) {
  // Outputs
       sc_out <sc_biguint<8> > rd_dataa;           // Read data for port A
       sc_out <sc_biguint<8> > rd_datab;           // Read data for port B
  // Inputs
       sc_in <sc_biguint<12> > addra;              // RAM address for port A
       sc_in <sc_biguint<12> > addrb;              // RAM address for port B
       sc_in <sc_biguint<8> >  wr_dataa;           // Write data for port A
       sc_in <sc_biguint<8> >  wr_datab;           // Write data for port B
       sc_in <bool >           wr_porta;           // Write enable for port A
       sc_in <bool >           en_porta;           // RAM enable for port A
       sc_in <bool >           wr_portb;           // Write enable for port B
       sc_in <bool >           en_portb;           // RAM enable for port B
       sc_in <bool >           clk;                // System clock
       sc_in <bool >           rst_n;              // System reset, active low

   
  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  sc_signal <sc_biguint<8> > rd_dataa_r;         // Registered read data for port A
  sc_signal <sc_biguint<8> > rd_datab_r;         // Registered read data for port B
  
  sc_signal <sc_biguint<8> > rd_dataa0;          // Read data port A RAM 0
  sc_signal <sc_biguint<8> > rd_datab0;          // Read data port B RAM 0
  sc_signal <sc_biguint<8> > rd_dataa1;          // Read data port A RAM 1
  sc_signal <sc_biguint<8> > rd_datab1;          // Read data port B RAM 1
  sc_signal <sc_biguint<8> > rd_dataa2;          // Read data port A RAM 2
  sc_signal <sc_biguint<8> > rd_datab2;          // Read data port B RAM 2
  sc_signal <sc_biguint<8> > rd_dataa3;          // Read data port A RAM 3
  sc_signal <sc_biguint<8> > rd_datab3;          // Read data port B RAM 3
  sc_signal <sc_biguint<8> > rd_dataa4;          // Read data port A RAM 4
  sc_signal <sc_biguint<8> > rd_datab4;          // Read data port B RAM 5
  sc_signal <sc_biguint<8> > rd_dataa5;          // Read data port A RAM 5
  sc_signal <sc_biguint<8> > rd_datab5;          // Read data port B RAM 6
  sc_signal <sc_biguint<8> > rd_dataa6;          // Read data port A RAM 6
  sc_signal <sc_biguint<8> > rd_datab6;          // Read data port B RAM 7
  sc_signal <sc_biguint<8> > rd_dataa7;          // Read data port A RAM 7
  sc_signal <sc_biguint<8> > rd_datab7;          // Read data port B RAM 7
  sc_signal <bool >          en_a0;              // Enable for port A of RAM 0 
  sc_signal <bool >          en_a1;              // Enable for port A of RAM 1  
  sc_signal <bool >          en_a2;              // Enable for port A of RAM 2  
  sc_signal <bool >          en_a3;              // Enable for port A of RAM 3  
  sc_signal <bool >          en_a4;              // Enable for port A of RAM 4  
  sc_signal <bool >          en_a5;              // Enable for port A of RAM 5  
  sc_signal <bool >          en_a6;              // Enable for port A of RAM 6  
  sc_signal <bool >          en_a7;              // Enable for port A of RAM 7   
  sc_signal <bool >          en_b0;              // Enable for port B of RAM 0  
  sc_signal <bool >          en_b1;              // Enable for port B of RAM 1  
  sc_signal <bool >          en_b2;              // Enable for port B of RAM 2  
  sc_signal <bool >          en_b3;              // Enable for port B of RAM 3  
  sc_signal <bool >          en_b4;              // Enable for port B of RAM 4  
  sc_signal <bool >          en_b5;              // Enable for port B of RAM 5  
  sc_signal <bool >          en_b6;              // Enable for port B of RAM 6  
  sc_signal <bool >          en_b7;              // Enable for port B of RAM 7
  sc_signal <bool >          en_porta_r;         // Registered enable for port A
  sc_signal <bool >          en_portb_r;         // Registered enable for port B
  sc_signal <bool >          rst;                // Reset inverted version of input
  sc_signal <sc_uint<9> >    raddra;
  sc_signal <sc_uint<9> >    raddrb;
  
  RAMB4_S8_S8 *io_i0, *io_i1, *io_i2, *io_i3, *io_i4, *io_i5, *io_i6, *io_i7;

   
  /****************************************************************************
   Generate the enable signals for the RAM's and the output data muxing
  ****************************************************************************/
   SC_CTOR (io_ram) {
	SC_METHOD (io_ram_combop);              
        sensitive << addra << addrb << en_porta << en_portb << rst_n;       
        SC_METHOD (io_ram_readap);
        sensitive << en_porta_r << addra << rd_dataa_r << rd_dataa0 << rd_dataa1 << rd_dataa2 << rd_dataa3 << rd_dataa4 << rd_dataa5 << rd_dataa6 << rd_dataa7;
        SC_METHOD (io_ram_readbp);
        sensitive << en_portb_r << addrb << rd_datab_r << rd_datab0 << rd_datab1 << rd_datab2 << rd_datab3 << rd_datab4 << rd_datab5 << rd_datab6 << rd_datab7;
        SC_METHOD (en_portap);
        sensitive_pos << clk;
        sensitive_neg << rst_n;
        SC_METHOD (en_portbp);
        sensitive_pos << clk;
        sensitive_neg << rst_n;
        SC_METHOD (rd_datab_rp);
        sensitive_pos << clk;
        sensitive_neg << rst_n;
        SC_METHOD (rd_dataa_rp);
        sensitive_pos << clk;
        sensitive_neg << rst_n;
	
  /****************************************************************************
   Instance the RAMS
  ****************************************************************************/	
    io_i0 = new RAMB4_S8_S8("i0");
    io_i1 = new RAMB4_S8_S8("i1");
    io_i2 = new RAMB4_S8_S8("i2");
    io_i3 = new RAMB4_S8_S8("i3");
    io_i4 = new RAMB4_S8_S8("i4");
    io_i5 = new RAMB4_S8_S8("i5");
    io_i6 = new RAMB4_S8_S8("i6");
    io_i7 = new RAMB4_S8_S8("i7");
 

    // Outputs
         io_i0->DOA       (rd_dataa0);
         io_i0->DOB       (rd_datab0);
    // Inputs
         io_i0->ADDRA     (raddra);         
         io_i0->CLKA      (clk);        
         io_i0->DIA       (wr_dataa);  
         io_i0->ENA       (en_a0);
         io_i0->WEA       (wr_porta);
         io_i0->RSTA      (rst);
         io_i0->ADDRB     (raddrb);         
         io_i0->CLKB      (clk);        
         io_i0->DIB       (wr_datab);  
         io_i0->ENB       (en_b0);
         io_i0->WEB       (wr_portb);
         io_i0->RSTB      (rst);

    // Outputs
         io_i1->DOA       (rd_dataa1);
         io_i1->DOB       (rd_datab1);
    // Inputs
         io_i1->ADDRA     (raddra);         
         io_i1->CLKA      (clk);        
         io_i1->DIA       (wr_dataa);  
         io_i1->ENA       (en_a1);
         io_i1->WEA       (wr_porta);
         io_i1->RSTA      (rst);
         io_i1->ADDRB     (raddrb);         
         io_i1->CLKB      (clk);        
         io_i1->DIB       (wr_datab);  
         io_i1->ENB       (en_b1);
         io_i1->WEB       (wr_portb);
         io_i1->RSTB      (rst);

    // Outputs
         io_i2->DOA       (rd_dataa2);
         io_i2->DOB       (rd_datab2);
    // Inputs
         io_i2->ADDRA     (raddra);         
         io_i2->CLKA      (clk);        
         io_i2->DIA       (wr_dataa);  
         io_i2->ENA       (en_a2);
         io_i2->WEA       (wr_porta);
         io_i2->RSTA      (rst);
         io_i2->ADDRB     (raddrb);         
         io_i2->CLKB      (clk);        
         io_i2->DIB       (wr_datab);  
         io_i2->ENB       (en_b2);
         io_i2->WEB       (wr_portb);
         io_i2->RSTB      (rst);
 
    // Outputs
         io_i3->DOA       (rd_dataa3);
         io_i3->DOB       (rd_datab3);
    // Inputs
         io_i3->ADDRA     (raddra);         
         io_i3->CLKA      (clk);        
         io_i3->DIA       (wr_dataa);  
         io_i3->ENA       (en_a3);
         io_i3->WEA       (wr_porta);
         io_i3->RSTA      (rst);
         io_i3->ADDRB     (raddrb);         
         io_i3->CLKB      (clk);        
         io_i3->DIB       (wr_datab);  
         io_i3->ENB       (en_b3);
         io_i3->WEB       (wr_portb);
         io_i3->RSTB      (rst);
  
    // Outputs
         io_i4->DOA       (rd_dataa4);
         io_i4->DOB       (rd_datab4);
    // Inputs
         io_i4->ADDRA     (raddra);         
         io_i4->CLKA      (clk);        
         io_i4->DIA       (wr_dataa);  
         io_i4->ENA       (en_a4);
         io_i4->WEA       (wr_porta);
         io_i4->RSTA      (rst);
         io_i4->ADDRB     (raddrb);         
         io_i4->CLKB      (clk);        
         io_i4->DIB       (wr_datab);  
         io_i4->ENB       (en_b4);
         io_i4->WEB       (wr_portb);
         io_i4->RSTB      (rst);

    // Outputs
         io_i5->DOA       (rd_dataa5);
         io_i5->DOB       (rd_datab5);
    // Inputs
         io_i5->ADDRA     (raddra);         
         io_i5->CLKA      (clk);        
         io_i5->DIA       (wr_dataa);  
         io_i5->ENA       (en_a5);
         io_i5->WEA       (wr_porta);
         io_i5->RSTA      (rst);
         io_i5->ADDRB     (raddrb);         
         io_i5->CLKB      (clk);        
         io_i5->DIB       (wr_datab);  
         io_i5->ENB       (en_b5);
         io_i5->WEB       (wr_portb);
         io_i5->RSTB      (rst);

    // Outputs
         io_i6->DOA       (rd_dataa6);
         io_i6->DOB       (rd_datab6);
    // Inputs
         io_i6->ADDRA     (raddra);         
         io_i6->CLKA      (clk);        
         io_i6->DIA       (wr_dataa);  
         io_i6->ENA       (en_a6);
         io_i6->WEA       (wr_porta);
         io_i6->RSTA      (rst);
         io_i6->ADDRB     (raddrb);         
         io_i6->CLKB      (clk);        
         io_i6->DIB       (wr_datab);  
         io_i6->ENB       (en_b6);
         io_i6->WEB       (wr_portb);
         io_i6->RSTB      (rst);
  
    // Outputs
         io_i7->DOA       (rd_dataa7);
         io_i7->DOB       (rd_datab7);
    // Inputs
         io_i7->ADDRA     (raddra);         
         io_i7->CLKA      (clk);        
         io_i7->DIA       (wr_dataa);  
         io_i7->ENA       (en_a7);
         io_i7->WEA       (wr_porta);
         io_i7->RSTA      (rst);
         io_i7->ADDRB     (raddrb);         
         io_i7->CLKB      (clk);        
         io_i7->DIB       (wr_datab);  
         io_i7->ENB       (en_b7);
         io_i7->WEB       (wr_portb);
         io_i7->RSTB      (rst);
     }
     
  void io_ram_combop ();
  void io_ram_readap ();  
  void io_ram_readbp ();  
  void en_portap ();
  void en_portbp ();
  void rd_datab_rp ();
  void rd_dataa_rp ();

 
  };
  
