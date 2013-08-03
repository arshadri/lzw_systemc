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
// Description: Clock and reset generator.
//
//*****************************************************************************
 
  #include "clk_rst.h"
  /****************************************************************************
   Drive dummy signals
  ****************************************************************************/
  void clk_rst::combop () {
    drive0.write(0);
    drive0_8bit.write(0);
  }
 
  /****************************************************************************
   Synchronize the input switch from FPGA board
  ****************************************************************************/
  void clk_rst::rstp () {
    if (rst.read()) {
      rst_s.write(0);
      rst_n.write(0);
    }
    else {
      rst_s.write(1);
      rst_n.write(rst_s.read());
    }
  }
 
  /****************************************************************************
   Divide clock 66MHZ by 2 to run the FPGA at 33MHZ. Just a safe clock speed.
  ****************************************************************************/
  void clk_rst::clkp () {
      clk.write(!clk.read());
  }
