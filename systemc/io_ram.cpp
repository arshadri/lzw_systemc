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

  #include "io_ram.h"
  /****************************************************************************
   Generate the enable signals for the RAM's and the output data muxing
  ****************************************************************************/
  void io_ram::io_ram_combop () {
    sc_uint<12 > laddra, laddrb, maddra, maddrb;
    laddra = sc_uint<12>(addra);
    laddrb = sc_uint<12>(addrb);
    maddra = sc_uint<12>(addra);
    maddrb = sc_uint<12>(addrb);
    raddra = (maddra[11],maddra[10],maddra[9],maddra[8],maddra[7],maddra[6],maddra[5],maddra[4],maddra[3]);
    raddrb = (maddrb[11],maddrb[10],maddrb[9],maddrb[8],maddrb[7],maddrb[6],maddrb[5],maddrb[4],maddrb[3]);
    rst.write(!rst_n.read());  
    en_a0.write(en_porta.read() &  (laddra[2,0] == 0));
    en_a1.write(en_porta.read() &  (laddra[2,0] == 1));
    en_a2.write(en_porta.read() &  (laddra[2,0] == 2));
    en_a3.write(en_porta.read() &  (laddra[2,0] == 3));
    en_a4.write(en_porta.read() &  (laddra[2,0] == 4));
    en_a5.write(en_porta.read() &  (laddra[2,0] == 5));
    en_a6.write(en_porta.read() &  (laddra[2,0] == 6));
    en_a7.write(en_porta.read() &  (laddra[2,0] == 7));  
    en_b0.write(en_portb.read() &  (laddrb[2,0] == 0));
    en_b1.write(en_portb.read() &  (laddrb[2,0] == 1));
    en_b2.write(en_portb.read() &  (laddrb[2,0] == 2));
    en_b3.write(en_portb.read() &  (laddrb[2,0] == 3));
    en_b4.write(en_portb.read() &  (laddrb[2,0] == 4));
    en_b5.write(en_portb.read() &  (laddrb[2,0] == 5));
    en_b6.write(en_portb.read() &  (laddrb[2,0] == 6));
    en_b7.write(en_portb.read() &  (laddrb[2,0] == 7));

  }

  void io_ram::io_ram_readap () {  
  	 sc_uint<12 > laddra;
    laddra = sc_uint<12>(addra);
    if (en_porta_r.read() & (laddra[2,0] == 0))
      rd_dataa.write(rd_dataa0.read());
    else if (en_porta_r.read() & (laddra[2,0] == 1))
      rd_dataa.write(rd_dataa1.read());
    else if (en_porta_r.read() & (laddra[2,0] == 2))
      rd_dataa.write(rd_dataa2.read());
    else if (en_porta_r.read() & (laddra[2,0] == 3))
      rd_dataa.write(rd_dataa3.read());
    else if (en_porta_r.read() & (laddra[2,0] == 4))
      rd_dataa.write(rd_dataa4.read());
    else if (en_porta_r.read() & (laddra[2,0] == 5))
      rd_dataa.write(rd_dataa5.read());
    else if (en_porta_r.read() & (laddra[2,0] == 6))
      rd_dataa.write(rd_dataa6.read());
    else if (en_porta_r.read() & (laddra[2,0] == 7))
      rd_dataa.write(rd_dataa7.read());
    else 
      rd_dataa.write(rd_dataa_r.read());
  }                                          

  void io_ram::io_ram_readbp () {  
  	 sc_uint<12 > laddrb;
    laddrb = sc_uint<12>(addrb);
    if (en_portb_r.read() & (laddrb[2,0] == 0))
      rd_datab.write(rd_datab0.read());
    else if (en_portb_r.read() & (laddrb[2,0] == 1))
      rd_datab.write(rd_datab1.read());
    else if (en_portb_r.read() & (laddrb[2,0] == 2))
      rd_datab.write(rd_datab2.read());
    else if (en_portb_r.read() & (laddrb[2,0] == 3))
      rd_datab.write(rd_datab3.read());
    else if (en_portb_r.read() & (laddrb[2,0] == 4))
      rd_datab.write(rd_datab4.read());
    else if (en_portb_r.read() & (laddrb[2,0] == 5))
      rd_datab.write(rd_datab5.read());
    else if (en_portb_r.read() & (laddrb[2,0] == 6))
      rd_datab.write(rd_datab6.read());
    else if (en_portb_r.read() & (laddrb[2,0] == 7))
      rd_datab.write(rd_datab7.read());
    else 
      rd_datab.write(rd_datab_r.read());
  }                                          

  void io_ram::en_portap () {
    if (!rst_n.read())
      en_porta_r.write(0);
    else
      en_porta_r.write(en_porta.read());
  } 
  
  void io_ram::en_portbp () {
    if (!rst_n.read())
      en_portb_r.write(0);
    else
      en_portb_r.write(en_portb.read());
  } 

  void io_ram::rd_datab_rp () {
    if (!rst_n.read())
      rd_datab_r.write(0);
    else if (en_portb_r.read())
      rd_datab_r.write(rd_datab.read());
  } 

  void io_ram::rd_dataa_rp () {
    if (!rst_n.read())
      rd_dataa_r.write(0);
    else if (en_porta_r.read())
      rd_dataa_r.write(rd_dataa.read());
  } 

