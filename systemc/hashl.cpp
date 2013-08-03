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
// Description: Hash generator.
//
//*****************************************************************************
  #include "hashl.h"
 
  /****************************************************************************
   Logic to determine if the current character is a hit in the dictionary
  ****************************************************************************/ 
  void hashl::hashl_combo () {
    not_in_mem.write((string_data.read() == 0x1FFF) & gen_hash_ss.read());
    cmp_append_char.write(append_data.read() == char_in.read());
    cmp_prefix_data.write(prefix_data.read() == string_reg.read());
  }

  void hashl::in_code_memp () {
    if (!rst_n.read())
      in_code_mem.write(0);
    else if (gen_hash.read())
      in_code_mem.write(0);
    else if (gen_hash_ss.read())
      in_code_mem.write((string_data.read() != 0x1FFF));
  }
  
  void hashl::matchp () {
    if (!rst_n.read())
      match.write(0);
    else if (gen_hash.read())
      match.write(0);
    else if (gen_hash_ss.read())
      match.write(cmp_append_char.read() & cmp_prefix_data.read());
  }

  void hashl::collisp () {
    if (!rst_n.read())
      collis.write(0);
    else if (gen_hash.read())
      collis.write(0);
    else if (gen_hash_ss.read())
      collis.write((cmp_append_char.read() & ~cmp_prefix_data.read()) 
                   | (~cmp_append_char.read() & cmp_prefix_data.read()));
  }

  /****************************************************************************
   Logic to generate hash
  ****************************************************************************/
  void hashl::genhashp() {
    if (!rst_n.read())
      gen_hash_s.write(0);
    else 
      gen_hash_s.write(gen_hash.read());
  }

  void hashl::genhashssp () {
    if (!rst_n.read())
      gen_hash_ss.write(0);
    else 
      gen_hash_ss.write(gen_hash_s.read());
  }

  void hashl::addrsavep () {
    if (!rst_n.read())
      addr_save.write(0);
    else 
      addr_save.write(index.read());
  }

  void hashl::indexp () {
    if (!rst_n.read())
      index.write(0);
    else if (gen_hash.read())
      index.write((char_in.read() << 5) ^ string_reg.read());
  }

void hashl::addrp () {
  	sc_uint<13 > addrls;
  	addrls = sc_uint<13>(addr_save);
    addr_saves = (addrls[11],addrls[10],addrls[9],addrls[8],addrls[7],addrls[6],addrls[5],addrls[4],addrls[3],addrls[2],addrls[1],addrls[0]);
  }
  
  void hashl::recalhashp () {
    if (recal_hash.read())
      addr.write(((0,addr_saves.read() + 12)));
    else
      addr.write(index.read());
  }
  
  void hashl::stringregp () {
    if (!rst_n.read())
      string_reg.write(0);
    else if (shift_char.read())
      string_reg.write(mux_code_val.read() ? string_data.read() : (0,char_in.read()));
  }
  
