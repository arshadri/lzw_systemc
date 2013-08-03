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
// Description: LZW encoder block, consists of controller and various RAM's.
//
//*****************************************************************************   
 #include "dictionary_ram.cpp"
 #include "code_value_ram.cpp"
 #include "hashl.cpp"
 #include "lzw_ctrl.cpp"
 #include "outreg.cpp" 
 #include "io_ram.cpp" 
 #include "lzw_enc.h"
 #include "systemc.h"

 /****************************************************************************
   Drive dummy signals
  ****************************************************************************/
  void lzw_enc::combo_lzwencp () {
    drive0.write(0);
    drive0_8bit.write(0);
    drive1_13bit.write(0x1fff);
  }
 
