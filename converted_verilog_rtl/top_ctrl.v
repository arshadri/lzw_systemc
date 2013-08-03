module top_ctrl(rst_n,clk,outram_cnt,char_in,xmt_done,rcv_done,lzw_done,done_cr,pwr_up,final_done,lzw_done_out,init_lzw_out,done_cr_out,init_cr_out,ser_recv_done,ena_outram,addra_outram,wea_ioram,ena_ioram,addra_ioram,start_xmt,char_cnt,init_lzw,init_cr);
input rst_n;
input clk;
input [11:0] outram_cnt;
input [7:0] char_in;
input xmt_done;
input rcv_done;
input lzw_done;
input done_cr;
output pwr_up;
output final_done;
output lzw_done_out;
output init_lzw_out;
output done_cr_out;
output init_cr_out;
output ser_recv_done;
output ena_outram;
output [11:0] addra_outram;
output wea_ioram;
output ena_ioram;
output [11:0] addra_ioram;
output start_xmt;
output [11:0] char_cnt;
output init_lzw;
output init_cr;

reg pwr_up;
reg final_done;
reg lzw_done_out;
reg init_lzw_out;
reg done_cr_out;
reg init_cr_out;
reg ser_recv_done;
reg ena_outram;
reg [11:0] addra_outram;
reg wea_ioram;
reg ena_ioram;
reg [11:0] addra_ioram;
reg start_xmt;
reg [11:0] char_cnt;
reg init_lzw;
reg init_cr;

parameter  DONE = 0,
           WT_TC = 1,
           WT_TC1 = 2,
           WT_TST = 3,
           LZWDONE = 4,
           WT_ST = 5,
           WT_RC = 6,
           WT_RST = 7,
           INIT_CR = 8,
           IDLE = 9;

reg idle;
reg done;
reg clr_aoutcntr;
reg [11:0] addr_outcntr;
reg clr_acntr;
reg [11:0] addr_cntr;
reg init_lzw_st;
reg inc_outraddr;
reg inc_ioraddr;
reg init_cr_st;
reg tc_outractr;
reg tc_ioractr;
reg [3:0] curr_st;
reg [3:0] nxt_st;


//process_final_done:
always @( done )
   begin

   final_done =done ;

   end
//process_clk10:
always @( posedge clk )
   begin

   if (rst_n ==0)
   lzw_done_out  <= (0);
   else if (lzw_done )
   lzw_done_out  <= (1);

   end
//process_clk9:
always @( posedge clk )
   begin

   if (rst_n ==0)
   done_cr_out  <= (0);
   else if (done_cr )
   done_cr_out  <= (1);

   end
//process_clk8:
always @( posedge clk )
   begin

   if (rst_n ==0)
   init_lzw_out  <= (0);
   else if (init_lzw_st )
   init_lzw_out  <= (1);

   end
//process_clk7:
always @( posedge clk )
   begin

   if (rst_n ==0)
   init_cr_out  <= (0);
   else if (init_cr_st )
   init_cr_out  <= (1);

   end
//process_clk6:
always @( posedge clk )
   begin

   if (rst_n ==0)
   ser_recv_done  <= (0);
   else if (tc_ioractr )
   ser_recv_done  <= (1);

   end
//process_clk5:
always @( posedge clk )
   begin

   if (rst_n ==0)
   pwr_up  <= (0);
   else if (idle )
   pwr_up  <= (1);

   end
//process_clk4:
always @( posedge clk )
   begin

   if (rst_n ==0)
   init_lzw  <= (0);
   else 
   init_lzw  <= (init_lzw_st );

   end
//process_clk3:
always @( posedge clk )
   begin

   if (rst_n ==0)
   init_cr  <= (0);
   else 
   init_cr  <= (init_cr_st );

   end
//process_addra_outram:
always @( addr_outcntr )
   begin

   addra_outram =addr_outcntr ;

   end
//process_tc_outractr:
always @( outram_cnt or addr_outcntr )
   begin

   tc_outractr =(addr_outcntr ==(outram_cnt +1));

   end
//process_clk2:
always @( posedge clk )
   begin

   if (rst_n ==0)
   addr_outcntr  <= ('h0);
   else if (clr_aoutcntr )
   addr_outcntr  <= ('h0);
   else if (inc_outraddr )
   addr_outcntr  <= (addr_outcntr +1);

   end
//process_char_cnt:
always @( addr_cntr )
   begin

   char_cnt =addr_cntr ;

   end
//process_addra_ioram:
always @( addr_cntr )
   begin

   addra_ioram =addr_cntr ;

   end
//process_tc_ioractr:
always @( char_in or addr_cntr )
   begin

   tc_ioractr =(addr_cntr =='hfff )|(char_in =='h0D );

   end
//process_clk1:
always @( posedge clk )
   begin

   if (rst_n ==0)
   addr_cntr  <= ('h0);
   else if (clr_acntr )
   addr_cntr  <= ('h0);
   else if (inc_ioraddr )
   addr_cntr  <= (addr_cntr +1);

   end
//process_clk:
always @( posedge clk )
   begin

   if (!rst_n )
   curr_st  <= (IDLE );
   else 
   curr_st  <= (nxt_st );

   end
//process_curr_st:
always @( tc_outractr or xmt_done or lzw_done or tc_ioractr or rcv_done or done_cr or curr_st )
   begin

   init_cr_st  = (0);
   inc_ioraddr  = (0);
   inc_outraddr  = (0);
   init_lzw_st  = (0);
   start_xmt  = (0);
   ena_ioram  = (0);
   wea_ioram  = (0);
   clr_acntr  = (0);
   ena_outram  = (0);
   clr_aoutcntr  = (0);
   done  = (0);
   idle  = (0);


   case(   curr_st )

      IDLE :
      begin
      idle  = (1);
      init_cr_st  = (1);
      nxt_st  = (INIT_CR );
      end

      INIT_CR :
      begin
       // Initiliaze Code RAM

         begin

         if (done_cr ==1)
         nxt_st  = (WT_RST );
         else 
         nxt_st  = (INIT_CR );
         end


         end

      WT_RST :
      begin
       // Wait Receive State

         begin

         nxt_st  = (WT_RC );
         end


         end

      WT_RC :
      begin
       // Wait for receive character

         begin

         if (rcv_done ==1)

            begin

            ena_ioram  = (1);
            wea_ioram  = (1);
            nxt_st  = (WT_ST );

            end

         else if (tc_ioractr ==1)

            begin

            init_lzw_st  = (1);
            nxt_st  = (LZWDONE );

            end

         else 
         nxt_st  = (WT_RC );
         end


         end

      WT_ST :
      begin
       // Wait State

         begin

         inc_ioraddr  = (1);
         nxt_st  = (WT_RST );
         end


         end

      LZWDONE :
      begin
       // Wait for LZW Done

         begin

         if (lzw_done ==1)

            begin

            nxt_st  = (WT_TST );
            clr_acntr  = (1);

            end

         else 
         nxt_st  = (LZWDONE );
         end


         end

      WT_TST :
      begin
       // Wait Transmit State

         begin

         nxt_st  = (WT_TC1 );
         start_xmt  = (1);
         ena_outram  = (1);
         end


         end

      WT_TC1 :
      begin
       // Wait for transmit character

         begin

         if (xmt_done ==1)

            begin

            start_xmt  = (0);
            nxt_st  = (WT_TC );

            end

         else 

            begin

            start_xmt  = (1);
            nxt_st  = (WT_TC1 );

            end

         end


         end

      WT_TC :
      begin
       // Wait for transmit character

         begin

         if ((tc_outractr ==1)&(xmt_done ==0))
         nxt_st  = (DONE );
         else if ((tc_outractr ==0)&(xmt_done ==0))

            begin

            inc_outraddr  = (1);
            ena_outram  = (1);
            nxt_st  = (WT_TST );

            end

         else 
         nxt_st  = (WT_TC );
         end


         end

      DONE :
      begin
       // All transmission finished

         begin

         done  = (1);
         nxt_st  = (DONE );
         end


         end

      default:
      begin
      nxt_st  = (IDLE );
      end



   endcase



   end
  //synthesis translate_off
  reg  [20*8:0] st_string;
  always @ (*)
  begin
    case (curr_st)
      IDLE   : st_string = "IDLE";
      INIT_CR: st_string = "INIT_CR";
      WT_RST : st_string = "WT_RST";
      WT_ST  : st_string = "WT_ST";
      WT_RC  : st_string = "WT_RC";
      LZWDONE: st_string = "LZWDONE";
      WT_TST : st_string = "WT_TST";
      WT_TC1 : st_string = "WT_TC1";
      WT_TC  : st_string = "WT_TC";
      DONE   : st_string = "DONE";
    endcase
  end
  //synthesis translate_on
endmodule
