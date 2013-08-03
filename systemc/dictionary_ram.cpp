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
// Description: Dictionary RAM.
//
//*****************************************************************************

  #include "dictionary_ram.h"
  
 /****************************************************************************
   Drive dummy signals
  ****************************************************************************/
  void dictionary_ram::combo_dictp () {
    sc_uint<13 > laddr;
    laddr = sc_uint<13>(addr);
    raddr = (laddr[11],laddr[10],laddr[9],laddr[8],laddr[7],laddr[6],laddr[5],laddr[4],laddr[3],laddr[2],laddr[1],laddr[0]);
    drive_1.write(1);
  }
 
