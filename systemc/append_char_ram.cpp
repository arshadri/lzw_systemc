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
   
  #include "append_char_ram.h"
  /****************************************************************************
   Different process for append character RAM
  ****************************************************************************/     
  void append_char_ram::append_char_ram_combop () {
    sc_uint<12 > laddr, maddr;
    laddr = sc_uint<12>(addr);
    maddr = sc_uint<12>(addr);
    raddr = (maddr[11],maddr[10],maddr[9],maddr[8],maddr[7],maddr[6],maddr[5],maddr[4],maddr[3]);
    rst.write(!rst_n.read());
    ram_en0.write(en.read() & (laddr[2,0] == 0)); 
    ram_en1.write(en.read() & (laddr[2,0] == 1)); 
    ram_en2.write(en.read() & (laddr[2,0] == 2)); 
    ram_en3.write(en.read() & (laddr[2,0] == 3)); 
    ram_en4.write(en.read() & (laddr[2,0] == 4)); 
    ram_en5.write(en.read() & (laddr[2,0] == 5)); 
    ram_en6.write(en.read() & (laddr[2,0] == 6)); 
    ram_en7.write(en.read() & (laddr[2,0] == 7)); 
  }

  void append_char_ram::append_char_ram_readp () {  
  	 sc_uint<12 > laddr;
    laddr = sc_uint<12>(addr);
    if (en_porta_r.read() & (laddr[2,0] == 0))
      rd_data.write(rd_data0.read());
    else if (en_porta_r.read() & (laddr[2,0] == 1))
      rd_data.write(rd_data1.read());
    else if (en_porta_r.read() & (laddr[2,0] == 2))
      rd_data.write(rd_data2.read());
    else if (en_porta_r.read() & (laddr[2,0] == 3))
      rd_data.write(rd_data3.read());
    else if (en_porta_r.read() & (laddr[2,0] == 4))
      rd_data.write(rd_data4.read());
    else if (en_porta_r.read() & (laddr[2,0] == 5))
      rd_data.write(rd_data5.read());
    else if (en_porta_r.read() & (laddr[2,0] == 6))
      rd_data.write(rd_data6.read());
    else if (en_porta_r.read() & (laddr[2,0] == 7))
      rd_data.write(rd_data7.read());
    else 
      rd_data.write(rd_data_r.read());
  }  
  
  void append_char_ram::en_portap () {
    if (!rst_n.read())
      en_porta_r.write(0);
    else
      en_porta_r.write(en.read());
  }
  
  void append_char_ram::rd_data_rp  () {
    if (!rst_n.read())
      rd_data_r.write(0);
    else if (en_porta_r.read())
      rd_data_r.write(rd_data.read());
  }

