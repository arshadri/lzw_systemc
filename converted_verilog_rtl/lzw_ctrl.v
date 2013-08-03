module lzw_ctrl(rst_n,clk,tc_outreg,valid_dcnt,collis,match,in_code_mem,not_in_mem,char_cnt,init_lzw,init_cr,write_sp,outram_cnt,mux_code_val,shift_char,write_data,read_data,wea_pcram,wea_acram,wea_cvram,ena_cvram,wr_cvdataa,web_cvram,enb_cvram,addrb_cvram,web_outram,enb_outram,addrb_outram,web_ioram,enb_ioram,addrb_ioram,recal_hash,gen_hash,lzw_done,done_cr);
input rst_n;
input clk;
input tc_outreg;
input valid_dcnt;
input collis;
input match;
input in_code_mem;
input not_in_mem;
input [11:0] char_cnt;
input init_lzw;
input init_cr;
output write_sp;
output [11:0] outram_cnt;
output mux_code_val;
output shift_char;
output write_data;
output read_data;
output wea_pcram;
output wea_acram;
output wea_cvram;
output ena_cvram;
output [12:0] wr_cvdataa;
output web_cvram;
output enb_cvram;
output [12:0] addrb_cvram;
output web_outram;
output enb_outram;
output [11:0] addrb_outram;
output web_ioram;
output enb_ioram;
output [11:0] addrb_ioram;
output recal_hash;
output gen_hash;
output lzw_done;
output done_cr;

reg write_sp;
reg [11:0] outram_cnt;
reg mux_code_val;
reg shift_char;
reg write_data;
reg read_data;
reg wea_pcram;
reg wea_acram;
reg wea_cvram;
reg ena_cvram;
reg [12:0] wr_cvdataa;
reg web_cvram;
reg enb_cvram;
reg [12:0] addrb_cvram;
reg web_outram;
reg enb_outram;
reg [11:0] addrb_outram;
reg web_ioram;
reg enb_ioram;
reg [11:0] addrb_ioram;
reg recal_hash;
reg gen_hash;
reg lzw_done;
reg done_cr;

parameter  LDONE = 0,
           FL_OUT = 1,
           SP_CHR = 2,
           CHK_CNT = 3,
           RD_OREG2 = 4,
           RD_OREG = 5,
           WR_OREG = 6,
           WT_RHASH = 7,
           WT_HASH = 8,
           GEN_HASH = 9,
           WT_DST2 = 10,
           RD_2NDCHAR = 11,
           WT_DST1 = 12,
           WT_LZWST = 13,
           LINIT_CR = 14,
           LIDLE = 15;

reg write_sp_r;
reg clr_ioacntr;
reg [11:0] outaddr_cntr;
reg [11:0] ioaddr_cntr;
reg [10:0] addr_cntr;
reg inc_cvadata;
reg recal_hash_st;
reg clr_acntr;
reg inc_cvbaddr_d;
reg inc_cvbaddr;
reg [12:0] data_cntr;
reg done_lzw_st;
reg inc_outraddr;
reg inc_ioraddr;
reg done_cr_st;
reg tc_cvactr;
reg tc_ioractr;
reg [3:0] curr_st;
reg [3:0] nxt_st;


//process_clk9:
always @( posedge clk )
   begin

   if (!rst_n )
   write_sp_r  <= (0);
   else if (done_lzw_st )
   write_sp_r  <= (0);
   else if (write_sp )
   write_sp_r  <= (1);

   end
//process_clk8:
always @( posedge clk )
   begin

   if (!rst_n )
   recal_hash  <= (0);
   else 
   recal_hash  <= (recal_hash_st );

   end
//process_clk7:
always @( posedge clk )
   begin

   if (!rst_n )
   lzw_done  <= (0);
   else 
   lzw_done  <= (done_lzw_st );

   end
//process_clk6:
always @( posedge clk )
   begin

   if (!rst_n )
   done_cr  <= (0);
   else 
   done_cr  <= (done_cr_st );

   end
//process_wr_cvdataa:
always @( data_cntr )
   begin

   wr_cvdataa =data_cntr ;

   end
//process_clk5:
always @( posedge clk )
   begin

   if (!rst_n )
   data_cntr  <= ('h100);
   else if (done_lzw_st )
   data_cntr  <= ('h100);
   else if (inc_cvadata )
   data_cntr  <= (data_cntr +1);

   end
//process_addrb_cvram:
always @( addr_cntr )
   begin

   addrb_cvram ={2'b00,addr_cntr[10:0] };

   end
//process_tc_cvactr:
always @( addr_cntr )
   begin

   tc_cvactr =(addr_cntr =='h7ff );

   end
//process_clk4:
always @( posedge clk )
   begin

   if (!rst_n )
   addr_cntr  <= ('h0);
   else if (clr_acntr )
   addr_cntr  <= ('h0);
   else if (inc_cvbaddr_d )
   addr_cntr  <= (addr_cntr +1);

   end
//process_clk3:
always @( posedge clk )
   begin

   if (!rst_n )
   inc_cvbaddr_d  <= (0);
   else 
   inc_cvbaddr_d  <= (inc_cvbaddr );

   end
//process_outram_cnt:
always @( outaddr_cntr )
   begin

   outram_cnt =outaddr_cntr ;

   end
//process_addrb_outram:
always @( outaddr_cntr )
   begin

   addrb_outram =outaddr_cntr ;

   end
//process_clk2:
always @( posedge clk )
   begin

   if (!rst_n )
   outaddr_cntr  <= ('h0);
   else if (inc_outraddr )
   outaddr_cntr  <= (outaddr_cntr +1);

   end
//process_addrb_ioram:
always @( ioaddr_cntr )
   begin

   addrb_ioram =ioaddr_cntr ;

   end
//process_tc_ioractr:
always @( char_cnt or ioaddr_cntr )
   begin

   tc_ioractr =(ioaddr_cntr ==char_cnt );

   end
//process_clk1:
always @( posedge clk )
   begin

   if (!rst_n )
   ioaddr_cntr  <= ('h0);
   else if (clr_ioacntr )
   ioaddr_cntr  <= ('h0);
   else if (inc_ioraddr )
   ioaddr_cntr  <= (ioaddr_cntr +1);

   end
//process_curr_st:
always @( tc_outreg or tc_ioractr or write_sp_r or valid_dcnt or collis or in_code_mem or match or not_in_mem or init_lzw or tc_cvactr or init_cr or curr_st )
   begin

   enb_cvram  = (0);
   web_cvram  = (0);
   inc_cvbaddr  = (0);
   done_cr_st  = (0);
   clr_acntr  = (0);
   enb_ioram  = (0);
   web_ioram  = (0);
   enb_outram  = (0);
   web_outram  = (0);
   shift_char  = (0);
   gen_hash  = (0);
   ena_cvram  = (1);
   wea_cvram  = (0);
   inc_cvadata  = (0);
   wea_acram  = (0);
   wea_pcram  = (0);
   recal_hash_st  = (0);
   write_data  = (0);
   read_data  = (0);
   done_lzw_st  = (0);
   inc_ioraddr  = (0);
   inc_outraddr  = (0);
   clr_ioacntr  = (0);
   mux_code_val  = (0);
   write_sp  = (0);


   case(   curr_st )

      LIDLE:
      begin
         begin
         if (init_cr )

            begin

            enb_cvram  = (1);
            web_cvram  = (1);
            inc_cvbaddr  = (1);
            ena_cvram  = (0);
            nxt_st  = (LINIT_CR );

            end

         else 
         nxt_st  = (LIDLE );
         end


         end

      LINIT_CR :
      begin
       // Initiliaze Code RAM

         begin

         if (tc_cvactr )

            begin

            done_cr_st  = (1);
            clr_acntr  = (1);
            nxt_st  = (WT_LZWST );

            end

         else 

            begin

            web_cvram  = (1);
            enb_cvram  = (1);
            inc_cvbaddr  = (1);
            ena_cvram  = (0);
            nxt_st  = (LINIT_CR );

            end

         end


         end

      WT_LZWST :
      begin
       // Wait for LZW start

         begin

         if (init_lzw )

            begin

            enb_ioram  = (1);
            nxt_st  = (WT_DST1 );

            end

         else 
         nxt_st  = (WT_LZWST );
         end


         end

      WT_DST1 :
      begin
       // Wait for Data1

         begin

         inc_ioraddr  = (1);
         shift_char  = (1);
         nxt_st  = (RD_2NDCHAR );
         end


         end

      RD_2NDCHAR :
      begin
       // Read second character from IO RAM

         begin

         enb_ioram  = (1);
         nxt_st  = (WT_DST2 );
         end


         end

      WT_DST2 :
      begin
       // Wait for Data2

         begin

         gen_hash  = (1);
         nxt_st  = (GEN_HASH );
         end


         end

      GEN_HASH :
      begin
       // Generate HASH

         begin

         ena_cvram  = (1);
         nxt_st  = (WT_HASH );
         end


         end

      WT_HASH :
      begin
       // Wait for HASH result

         begin

         if (not_in_mem ) // Not in memory write data into all RAM s

            begin

            wea_cvram  = (1);
            inc_cvadata  = (1);
            wea_acram  = (1);
            wea_pcram  = (1);
            nxt_st  = (WR_OREG );

            end

         else if (match ) // Match in dictionary

            begin

            mux_code_val  = (1);
            shift_char  = (1);
            nxt_st  = (CHK_CNT );

            end

         else if (in_code_mem ) // Match in code memory

            begin

            mux_code_val  = (1);
            nxt_st  = (WR_OREG );

            end

         else if (collis ) // Collision generate during hash , recaluclate

            begin

            recal_hash_st  = (1);
            nxt_st  = (WT_RHASH );

            end

         else 
         nxt_st  = (WT_HASH );
         end


         end

      WT_RHASH :
      begin
       // Wait for recalculate HASH result

         begin

         if (not_in_mem )

            begin

            wea_cvram  = (1);
            inc_cvadata  = (1);
            wea_acram  = (1);
            wea_pcram  = (1);
            nxt_st  = (WR_OREG );

            end

         else if (match ) // Match in dictionary

            begin

            mux_code_val  = (1);
            shift_char  = (1);
             // nxt_st .write ( CHK_CNT ) ;
            nxt_st  = (RD_2NDCHAR );

            end

         else if (in_code_mem ) // Match in code memory

            begin

            nxt_st  = (WR_OREG );

            end

         else if (collis ) // Wait for recalculate HASH result

            begin

            recal_hash_st  = (1);
            nxt_st  = (WT_HASH );

            end

         else 
         nxt_st  = (WT_RHASH );
         end


         end

      WR_OREG :
      begin
       // Write to output data register

         begin

         if (in_code_mem )
         mux_code_val  = (1);
         else 
         mux_code_val  = (0);
         write_data  = (1);
         shift_char  = (1);
         nxt_st  = (RD_OREG );
         end


         end

      RD_OREG :
      begin
       // Read from output data register and write to IORAM

         begin

         read_data  = (1);
         web_outram  = (1);
         enb_outram  = (1);
         inc_outraddr  = (1);
         nxt_st  = (RD_OREG2 );
         end


         end

      RD_OREG2 :
      begin
       // If greater than8 - bits data than read again

         begin

         if (valid_dcnt )

            begin

            read_data  = (1);
            web_outram  = (1);
            enb_outram  = (1);
            inc_outraddr  = (1);
            nxt_st  = (RD_OREG2 );

            end

         else 

            begin

            enb_outram  = (0);
            web_outram  = (0);
            inc_outraddr  = (0);
            nxt_st  = (CHK_CNT );

            end

         end


         end

      CHK_CNT :
      begin
       // Check that IO address counter is at max . value or not

         begin

         if (write_sp_r )

            begin

            nxt_st  = (FL_OUT );

            end

         else if (tc_ioractr &!match &!write_sp_r )

            begin

            write_sp  = (1);
            nxt_st  = (SP_CHR );

            end

         else if (tc_ioractr &match &!write_sp_r )

            begin

            inc_outraddr  = (1);
            write_sp  = (1);
            nxt_st  = (SP_CHR );

            end

         else if (match )

            begin

            inc_ioraddr  = (1);
            nxt_st  = (RD_2NDCHAR );

            end

         else  // ~ match case

            begin

            inc_ioraddr  = (1);
            nxt_st  = (RD_2NDCHAR );

            end

         end


         end

      SP_CHR :
      begin
       // Write special character

         begin

         nxt_st  = (RD_OREG );
         end


         end

      FL_OUT :
      begin
       // All transmission finished

         begin

         if (tc_outreg )

            begin

            nxt_st  = (LDONE );

            end

         else  // Less than byte left in outreg , flush it

            begin

            read_data  = (1);
            web_outram  = (1);
            enb_outram  = (1);
            done_lzw_st  = (1);
            nxt_st  = (LDONE );

            end

         end


         end

      LDONE :
      begin
       // All transmission finished

         begin

         nxt_st  = (LIDLE );
         done_lzw_st  = (1);
         end


         end

      default:
      begin
      nxt_st  = (LIDLE );
      end


   endcase


   end
//process_clk:
always @( posedge clk )
   begin

   if (!rst_n )
   curr_st  <= (LIDLE );
   else 
   curr_st  <= (nxt_st );

   end
  //synthesis translate_off
  reg  [20*8:0] st_string;
  always @ (*)
  begin
    case (curr_st)
      LIDLE     : st_string = "LIDLE";     
      LINIT_CR  : st_string = "LINIT_CR";  
      WT_LZWST  : st_string = "WT_LZWST";  
      WT_DST1   : st_string = "WT_DST1";  
      RD_2NDCHAR: st_string = "RD_2NDCHAR"; 
      WT_DST2   : st_string = "WT_DST2";  
      GEN_HASH  : st_string = "GEN_HASH"; 
      WT_HASH   : st_string = "WT_HASH";   
      WT_RHASH  : st_string = "WT_RHASH";  
      WR_OREG   : st_string = "WR_OREG";   
      RD_OREG   : st_string = "RD_OREG";   
      RD_OREG2  : st_string = "RD_OREG2";   
      CHK_CNT   : st_string = "CHK_CNT";     
      SP_CHR    : st_string = "SP_CHR";     
      FL_OUT    : st_string = "FL_OUT";   
      LDONE     : st_string = "LDONE";     
    endcase      
  end
  //synthesis translate_on
endmodule
