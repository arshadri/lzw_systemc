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
// Description: Test case for sending a 4Kbyte packet with all "c" to see 
//              compression working
//***************************************************************************** 

  `define EOF_CODE 8'h0D   
  `timescale  1 ns / 1 ns
  module test1;
  
  integer i;
  
  initial 
  begin
  // Wait for resets and initilization of Code value RAM to be over before 
  // transmitting Serial code.
  wait (~tb.rst);
  $display ($time, "\tTEST: Reset Deasserted");
  wait (tb.init_cr);
  wait (tb.done_cr);
  repeat (10) @(posedge tb.clk);
  $display ($time, "\tTEST: Code RAM initialized");
  
  // Transmit ASCII code from serial port to FPGA
  for (i=0; i<4096; i=i+1)  
    tb.ser_model.write(8'h63); // char c


  wait (tb.lzw_done);
  wait (tb.final_done);
  repeat (20) @(posedge tb.clk);
  #200 $finish;
  end
  
  // Instance top level tb
  tb tb();
  
  endmodule