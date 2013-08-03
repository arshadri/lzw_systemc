module ser(rst_n,clk,start_xmt,sin,xmt_byte,vld_str_deb,xmt_done,rcv_done,sout,rcv_byte);
input rst_n;
input clk;
input start_xmt;
input sin;
input [7:0] xmt_byte;
output vld_str_deb;
output xmt_done;
output rcv_done;
output sout;
output [7:0] rcv_byte;

reg vld_str_deb;
reg xmt_done;
reg rcv_done;
reg sout;
reg [7:0] rcv_byte;

wire [7:0] rbit;
reg bout0;
reg ld_data;
reg sclk;
reg tc_rcv_cnt16;
reg tc_rcv_cnt;
reg tc_xmt_cnt16;
reg tc_xmt_cnt;
reg tc;
reg xmt_done_ss;
reg xmt_done_s;
reg rcv_done_ss;
reg rcv_done_s;
reg valid_start;
reg [7:0] sclk_cntr;
reg [3:0] rcv_cnt16;
reg [3:0] rcv_cnt;
reg [3:0] cnt;
reg [3:0] xmt_cnt16;
reg [3:0] xmt_cnt;
reg [8:0] byte_in;
reg [9:0] bout;

reg [9:0] bout_bitsser_combop;
reg [8:0] lbitser_combop;
reg [7:0] rbitser_combop;

//boutp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   bout  <=('h1);
   else if (ld_data )
   bout  <=({1'b1,xmt_byte[7:0] ,1'b0});
   else if (!start_xmt |(start_xmt &tc_xmt_cnt16 &xmt_cnt ==9)&sclk )
   bout  <=('h1);
   else if (start_xmt &tc_xmt_cnt16 &sclk )
   bout  <=(bout >>1);

   end
//rcv_bytep:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   rcv_byte  <=(0);
   else if (tc_rcv_cnt &sclk )
   rcv_byte  <=(byte_in );

   end
//byte_inp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   byte_in  <=(0);
   else if (valid_start &tc_rcv_cnt16 &sclk )
   byte_in  <=({sin ,rbitser_combop[7:0]});

   end
//rcv_done_sp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
      begin

      rcv_done_s  <=(0);
      rcv_done_ss  <=(0);

      end

   else 
      begin

      rcv_done_s  <=(tc_rcv_cnt );
      rcv_done_ss  <=(rcv_done_s );

      end


   end
//rcv_cntp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   rcv_cnt  <=(0);
   else if (~valid_start &sclk )
   rcv_cnt  <=(0);
   else if (valid_start &tc_rcv_cnt16 &sclk )
   rcv_cnt  <=(rcv_cnt +1);

   end
//rcv_cnt16p:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   rcv_cnt16  <=(0);
   else if (~valid_start &sclk )
   rcv_cnt16  <=(0);
   else if (valid_start &sclk )
   rcv_cnt16  <=(rcv_cnt16 +1);

   end
//vld_str_debp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   vld_str_deb  <=(0);
   else if (valid_start )
   vld_str_deb  <=(1);

   end
//valid_startp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   valid_start  <=(0);
   else if (tc_rcv_cnt )
   valid_start  <=(0);
   else if (tc )
   valid_start  <=(1);

   end
//cntp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   cnt  <=('hf );
   else if ((sin |tc |valid_start )&sclk )
   cnt  <=('hf );
   else if (!sin &sclk )
   cnt  <=(cnt -1);

   end
//xmt_donesp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
      begin

      xmt_done_s  <=(0);
      xmt_done_ss  <=(0);

      end

   else 
      begin

      xmt_done_s  <=(start_xmt );
      xmt_done_ss  <=(xmt_done_s );

      end


   end
//xmt_cntp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   xmt_cnt  <=(0);
   else if (!start_xmt &sclk )
   xmt_cnt  <=(0);
   else if (start_xmt &tc_xmt_cnt16 &sclk )
   xmt_cnt  <=(xmt_cnt +1);

   end
//xmt_cnt16p:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   xmt_cnt16  <=(0);
   else if (!start_xmt &sclk )
   xmt_cnt16  <=(0);
   else if (start_xmt &sclk )
   xmt_cnt16  <=(xmt_cnt16 +1);

   end
//sclk_cntrp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   sclk_cntr  <=(0);
   else if (sclk_cntr ==17)
   sclk_cntr  <=(0);
   else 
   sclk_cntr  <=(sclk_cntr +1);

   end
//ser_combop:
always @(rcv_done_ss or rcv_done_s or rcv_cnt or rcv_cnt16 or cnt or bout or xmt_done_s or tc_xmt_cnt or xmt_cnt or xmt_cnt16 or sclk_cntr or xmt_done_ss or byte_in )
   begin

   bout_bitsser_combop=(bout );


   lbitser_combop=(byte_in );

   bout0  =(bout_bitsser_combop[0]);
   sclk  =(sclk_cntr ==17);
   tc_xmt_cnt16  =(xmt_cnt16 =='hf );
   tc_xmt_cnt  =(xmt_cnt =='ha );
   xmt_done  =(tc_xmt_cnt );
   ld_data  =(xmt_done_s &!xmt_done_ss );
   sout  =(bout0 ); //Serial data out
   tc  =(cnt ==0);
   tc_rcv_cnt16  =(rcv_cnt16 =='hf );
   tc_rcv_cnt  =(rcv_cnt ==9);
   rcv_done  =(!rcv_done_s &rcv_done_ss );
   rbitser_combop={lbitser_combop[8],lbitser_combop[7],lbitser_combop[6],lbitser_combop[5],lbitser_combop[4],lbitser_combop[3],lbitser_combop[2],lbitser_combop[1]};

   end
  //synthesis translate_off
  always @ (posedge clk)
  begin
    if (tc_rcv_cnt & sclk)
    begin
      $display ($time, "\SER: Received Byte = %h", byte_in[7:0]);
    end
  end
  //synthesis translate_on
endmodule
