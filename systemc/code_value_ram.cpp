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
  #include "code_value_ram.h"
  
   /****************************************************************************
   Generate the enable signals for the RAM's and the output data muxing
  ****************************************************************************/
  void code_value_ram::code_value_ram_combop () {
    sc_uint<13 > laddra, maddra, maddrb;
    laddra = sc_uint<13>(addra);
    maddra = sc_uint<13>(addra);
    maddrb = sc_uint<13>(addrb);
    raddra = (maddra[11],maddra[10],maddra[9],maddra[8],maddra[7],maddra[6],maddra[5],maddra[4],maddra[3],maddra[2]);
    raddrb = (maddrb[9],maddrb[8],maddrb[7],maddrb[6],maddrb[5],maddrb[4],maddrb[3],maddrb[2],maddrb[1],maddrb[0]);
    rst.write(!rst_n.read());  
    en_a0.write(en_porta.read() &  (laddra[1,0] == 0));
    en_a1.write(en_porta.read() &  (laddra[1,0] == 1));
    en_a2.write(en_porta.read() &  (laddra[1,0] == 2));
    en_a3.write(en_porta.read() &  (laddra[1,0] == 3));
    drive0_3.write(0);
    wr_dataac=(0,wr_dataa);
    wr_databc=(0,wr_datab);
  }

  void code_value_ram::code_value_ram_readap () {  
  	 sc_uint<13 > laddra;
    laddra = sc_uint<13>(addra);
    if (en_porta_r.read() & (laddra[1,0] == 0))
      rd_dataa.write(rd_dataa0.read());
    else if (en_porta_r.read() & (laddra[1,0] == 1))
      rd_dataa.write(rd_dataa1.read());
    else if (en_porta_r.read() & (laddra[1,0] == 2))
      rd_dataa.write(rd_dataa2.read());
    else if (en_porta_r.read() & (laddra[1,0] == 3))
      rd_dataa.write(rd_dataa3.read());
    else 
      rd_dataa.write(rd_dataa_r.read());
  }                               
  
  void code_value_ram::en_portap () {
    if (!rst_n.read())
      en_porta_r.write(0);
    else
      en_porta_r.write(en_porta.read());
  } 

  void code_value_ram::rd_dataa_rp () {
    if (!rst_n.read())
      rd_dataa_r.write(0);
    else if (en_porta_r.read())
      rd_dataa_r.write(rd_dataa.read());
  } 
  
