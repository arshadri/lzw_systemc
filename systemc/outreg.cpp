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
// Description: Shift register for combining and outputting LZW encoded 
//              data to IORAM 
//
//*****************************************************************************
    #include "outreg.h"
 
  /****************************************************************************
   Shift register for combining and outputting data to IORAM
  ****************************************************************************/
  void outreg::outreg_combop () {
   flush.write(read_data.read() & (datain_cnt.read() < 8));  
   tc_outreg.write(datain_cnt.read() == 0);
   valid_dcnt.write(datain_cnt.read() >= 8);
   lzw_byte.write(shift_reg.read() >> 24);
  }

  void outreg::datain_cntp () {
   if (!rst_n.read())
     datain_cnt.write(0);  
   else if (flush.read())
     datain_cnt.write(0); 
   else {
     if (read_data.read() & !write_data.read() & !write_sp.read())
        datain_cnt.write(datain_cnt - 8);
     else if (!read_data.read() & write_data.read() & !write_sp.read())
        datain_cnt.write(datain_cnt + 13);
     else if (!read_data.read() & !write_data.read() & write_sp.read())
        datain_cnt.write(datain_cnt + 13);
     else
        datain_cnt.write(datain_cnt);
   }
  }

  void outreg::shift_regp () {
   if (!rst_n.read())
     shift_reg.write(0);  
   else if (write_data.read())
     shift_reg.write(shift_reg.read() | (prefix_data.read() << (19-datain_cnt.read()))); 
   else if (write_sp.read())
     shift_reg.write(shift_reg.read() | ((19-datain_cnt.read()) << 0x1fff));
   else if (read_data.read())
     shift_reg.write(shift_reg.read() << 8 ); 
  }
