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
// Description: Top most level block of the LZW implementation.
//
//*****************************************************************************

 // #include "clk_rst.h"
 // #include "lzw_io_ram.h"
 // #include "lzw_enc.h"
//  #include "top_ctrl.h"
 // #include "ser.h"
  #include <systemc.h>
  /****************************************************************************
   Top most level block of the LZW implementation
  ****************************************************************************/
  SC_MODULE (lzw) { 
  	
    sc_out <bool > tx;                 // serial transmit data
    sc_out <bool > ser_recv_done;      // serial port data receive done
    sc_out <bool > init_cr;            // initialize code value ram
    sc_out <bool > init_lzw;           // initialize lzw main state machine
    sc_out <bool > done_cr;            // code value ram initilization done
    sc_out <bool > lzw_done;           // lzw done with processing all data
    sc_out <bool > final_done;         // all transactions have finished
    sc_out <bool > pwr_up;             // power up for debug purpose on fpga
    sc_out <bool > valid_start_deb;    // valid start on rx detected for debug

    sc_in  <bool > rx;                 // serial receive data
    sc_in  <bool > clk66;              // system clock, 66mhz
    sc_in  <bool > rst;                // System reset, active high
  /****************************************************************************
   Internal declarations
  ****************************************************************************/ 
  
  sc_signal <sc_biguint<8> >  rcv_byte;    // Receive byte from serial port
  sc_signal <sc_biguint<8> >  lzw_byte;    // Output byte from LZW output forming logic  
  sc_signal <sc_biguint<8> >  char_in;     // Read data from IO RAM port A
  sc_signal <sc_biguint<8> >  xmt_byte;    // Read data from IO RAM port B
  sc_signal <sc_biguint<12> > addra_ioram; // Address for port A of IO RAM
  sc_signal <sc_biguint<12> > addrb_ioram; // Address for port B of IO RAM
  sc_signal <sc_biguint<12> > addra_outram;// Address for port A of out RAM
  sc_signal <sc_biguint<12> > outram_cnt;  // Output RAM data count
  sc_signal <sc_biguint<12> > char_cnt;    // Number of characters received  
  
  sc_signal <bool >    wea_ioram;          // Write enable for port A of IO RAM
  sc_signal <bool >    ena_ioram;          // Enable for port A of IO RAM
  sc_signal <bool >    web_ioram;          // Write enable for port B of IO RAM
  sc_signal <bool >    enb_ioram;          // Enable for port B of IO RAM
  sc_signal <bool >    ena_outram;         // Enable for port A of out RAM
  sc_signal <bool >    rcv_done;           // Reception of byte complete   
  sc_signal <bool >    xmt_done;           // Transmission of byte complete
  sc_signal <bool >    init_cr_out;        // Initiliaze code value ram debug out
  sc_signal <bool >    done_cr_out;        // Done initiliaze code value ram debug out
  sc_signal <bool >    init_lzw_out;       // LZW start debug out
  sc_signal <bool >    lzw_done_out;       // LZW done debug out
  sc_signal <bool >    start_xmt;          // Start serial transmission
    
  sc_signal <bool >    clk;                // Clock 33 MHZ used everywhere
  sc_signal <bool >    rst_n;              // Synchronized reset, active low
  sc_signal <bool >    drive0;             // Drive 0
  sc_signal <sc_biguint<8> > drive0_8bit;     // Drive 0 for 8-bits
  sc_signal <sc_biguint<8> > dummy1;          // Dummy output

  
   clk_rst *clk_rst1;
   ser  *ser1;
   top_ctrl *top_ctrl1;
   lzw_enc  *lzw_enc1;
   lzw_io_ram   *lzw_io_ram2;
 
    SC_CTOR(lzw) {
	
     clk_rst1  = new clk_rst("clk_rst");
     ser1      = new ser("ser");
     top_ctrl1 = new top_ctrl("top_ctrl");
     lzw_enc1  = new lzw_enc("lzw_enc");
     lzw_io_ram2   = new lzw_io_ram("lzw_io_ram");
  
  /****************************************************************************
   Instance the Clock reset block
  ****************************************************************************/
    // Outputs
         clk_rst1->clk           (clk);             // To all blocks
         clk_rst1->rst_n         (rst_n);           // To all blocks
         clk_rst1->drive0        (drive0);          // To all blocks
         clk_rst1->drive0_8bit   (drive0_8bit);     // To all blocks
    // Inputs                               
         clk_rst1->clk66         (clk66);           // From iopads
         clk_rst1->rst           (rst);             // From iopads
         
  /****************************************************************************
   Instance the input/output RAM
  ****************************************************************************/
    // Outputs
         lzw_io_ram2->rd_dataa       (dummy1);                
         lzw_io_ram2->rd_datab       (char_in);         // To lzw_enc
    // Inputs                               
         lzw_io_ram2->wr_porta       (wea_ioram);       // From top_ctrl    
         lzw_io_ram2->en_porta       (ena_ioram);       // From top_ctrl    
         lzw_io_ram2->addra          (addra_ioram);     // From top_ctrl
         lzw_io_ram2->wr_dataa       (rcv_byte);        // From ser
         lzw_io_ram2->wr_portb       (drive0);          // From lzw_enc
         lzw_io_ram2->en_portb       (enb_ioram);       // From lzw_enc
         lzw_io_ram2->addrb          (addrb_ioram);     // From lzw_enc        
         lzw_io_ram2->wr_datab       (drive0_8bit);     // From lzw_enc
         lzw_io_ram2->clk            (clk);             // From iopads
         lzw_io_ram2->rst_n          (rst_n);           // From iopads

  /****************************************************************************
   Instance the LZW encoder block
  ****************************************************************************/ 
    // Outputs
         lzw_enc1->xmt_byte       (xmt_byte);        // To IO RAM
         lzw_enc1->web_ioram      (web_ioram);       // To IO RAM
         lzw_enc1->enb_ioram      (enb_ioram);       // To IO RAM
         lzw_enc1->addrb_ioram    (addrb_ioram);     // To IO RAM
         lzw_enc1->lzw_done       (lzw_done);        // To top_ctrl
         lzw_enc1->done_cr        (done_cr);         // To top_ctrl
         lzw_enc1->outram_cnt     (outram_cnt);      // To top_ctrl
    // Inputs
         lzw_enc1->addra_outram   (addra_outram);    // To out RAM
         lzw_enc1->ena_outram     (ena_outram);      // To out RAM
         lzw_enc1->init_cr        (init_cr);         // From top_ctrl
         lzw_enc1->init_lzw       (init_lzw);        // From top_ctrl   
         lzw_enc1->char_cnt       (char_cnt);        // From top_ctrl 
         lzw_enc1->char_in        (char_in);         // From IO RAM
         lzw_enc1->clk            (clk);             // From iopads
         lzw_enc1->rst_n          (rst_n);           // From iopads
   
  /****************************************************************************
   Instance the top level controller block
  ****************************************************************************/ 
    // Outputs
         top_ctrl1->init_cr        (init_cr);         // To lzw_ctrl       
         top_ctrl1->init_lzw       (init_lzw);        // To lzw_ctrl     
         top_ctrl1->char_cnt       (char_cnt);        // To lzw_ctrl
         top_ctrl1->start_xmt      (start_xmt);       // To ser
         top_ctrl1->addra_ioram    (addra_ioram);     // To IO RAM
         top_ctrl1->ena_ioram      (ena_ioram);       // To IO RAM
         top_ctrl1->wea_ioram      (wea_ioram);       // To IO RAM
         top_ctrl1->addra_outram   (addra_outram);    // To out RAM
         top_ctrl1->ena_outram     (ena_outram);      // To out RAM
         top_ctrl1->ser_recv_done  (ser_recv_done);   // To iopads
         top_ctrl1->init_cr_out    (init_cr_out);     // To iopads
         top_ctrl1->done_cr_out    (done_cr_out);     // To iopads
         top_ctrl1->init_lzw_out   (init_lzw_out);    // To iopads
         top_ctrl1->lzw_done_out   (lzw_done_out);    // To iopads
         top_ctrl1->final_done     (final_done);      // To iopads
         top_ctrl1->pwr_up         (pwr_up);          // To iopads
    // Inputs
         top_ctrl1->done_cr        (done_cr);         // From lzw_ctrl
         top_ctrl1->lzw_done       (lzw_done);        // From lzw_ctrl
         top_ctrl1->outram_cnt     (outram_cnt);      // From lzw_ctrl
         top_ctrl1->rcv_done       (rcv_done);        // From ser
         top_ctrl1->xmt_done       (xmt_done);        // From ser
         top_ctrl1->char_in        (rcv_byte);        // From ser
         top_ctrl1->clk            (clk);             // From iopads
         top_ctrl1->rst_n          (rst_n);           // From iopads
  
  /****************************************************************************
   Instance the serial port
  ****************************************************************************/ 
    // Outputs
         ser1->sout                (tx);              // To iopads
         ser1->rcv_byte            (rcv_byte);        // To io_ram
         ser1->rcv_done            (rcv_done);        // To top_ctrl
         ser1->xmt_done            (xmt_done);        // To top_ctrl
         ser1->vld_str_deb         (valid_start_deb); // To iopads
    // Inputs		                         
         ser1->sin                 (rx);              // From iopads
         ser1->start_xmt           (start_xmt);       // From top_ctrl
         ser1->xmt_byte            (xmt_byte);        // From io_ram
         ser1->clk                 (clk);	            // From iopads
         ser1->rst_n               (rst_n);           // From iopads
   }
   
 };
