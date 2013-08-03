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
// Description: Verilog Testbench for veifying the LZW implementation
//    
//***************************************************************************** 
`timescale 1ps/1ps
  /****************************************************************************
  
  ****************************************************************************/
module tb ();
  
  wire          tx;                 // Serial transmit data
  wire          ser_recv_done;      // Serial port data receive done
  wire          init_cr;            // Initialize code value RAM
  wire          init_lzw;           // Initialize LZW main state machine
  wire          done_cr;            // Code value RAM initilization done
  wire          lzw_done;           // LZW done with processing all data
  wire          final_done;         // All transactions have finished   
  wire          pwr_up;             // Power up for debug purpose on FPGA
  wire          valid_start_deb;    // Valid start on Rx detected for debug
  wire          rx;                 // Serial receive data
  
  reg           clk;                // System clock
  reg           rst;                // System reset, active high

  /****************************************************************************
   Clock generation logic. Generate 66MHZ clock to match FPGA board clock
  ****************************************************************************/ 
  initial 
  begin
    clk = 1'b0;  
    forever #(7500) clk = ~clk;
  end
  
  /****************************************************************************
   Clock generation logic
  ****************************************************************************/ 
  initial 
  begin
    rst = 1'b1;  
    #89000 rst = 1'b0;
  end
  
  /****************************************************************************
   Instance the block under test
  ****************************************************************************/  
  lzw lzw (
    // Outputs
         .tx              (tx),
         .ser_recv_done   (ser_recv_done),
         .init_cr         (init_cr),      
         .init_lzw        (init_lzw),     
         .done_cr         (done_cr),      
         .lzw_done        (lzw_done),     
         .final_done      (final_done),     
         .pwr_up          (pwr_up),     
         .valid_start_deb (valid_start_deb),   
    // Inputs            
         .rx              (rx),
         .clk66           (clk), 
         .rst             (rst)
  );

  /****************************************************************************
   Instance the serial port model
  ****************************************************************************/  
  ser_model ser_model (
    // Outputs
         .sout            (rx),
    // Inputs             
         .sin             (tx),
         .rst             (rst)
  );

endmodule //tb  