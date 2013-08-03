module append_char_ram(rst_n,clk,en,wren,wr_data,addr,rd_data);
input rst_n;
input clk;
input en;
input wren;
input [7:0] wr_data;
input [11:0] addr;
output [7:0] rd_data;

reg [7:0] rd_data;

reg [8:0] raddr;
reg rst;
reg en_porta_r;
reg ram_en7;
reg ram_en6;
reg ram_en5;
reg ram_en4;
reg ram_en3;
reg ram_en2;
reg ram_en1;
reg ram_en0;
wire [7:0] rd_data7;
wire [7:0] rd_data6;
wire [7:0] rd_data5;
wire [7:0] rd_data4;
wire [7:0] rd_data3;
wire [7:0] rd_data2;
wire [7:0] rd_data1;
wire [7:0] rd_data0;
reg [7:0] rd_data_r;

RAMB4_S8 i7 (.RST(rst), .WE(wren), .EN(ram_en7), .DI(wr_data), .CLK(clk), .ADDR(raddr), .DO(rd_data7));
RAMB4_S8 i6 (.RST(rst), .WE(wren), .EN(ram_en6), .DI(wr_data), .CLK(clk), .ADDR(raddr), .DO(rd_data6));
RAMB4_S8 i5 (.RST(rst), .WE(wren), .EN(ram_en5), .DI(wr_data), .CLK(clk), .ADDR(raddr), .DO(rd_data5));
RAMB4_S8 i4 (.RST(rst), .WE(wren), .EN(ram_en4), .DI(wr_data), .CLK(clk), .ADDR(raddr), .DO(rd_data4));
RAMB4_S8 i3 (.RST(rst), .WE(wren), .EN(ram_en3), .DI(wr_data), .CLK(clk), .ADDR(raddr), .DO(rd_data3));
RAMB4_S8 i2 (.RST(rst), .WE(wren), .EN(ram_en2), .DI(wr_data), .CLK(clk), .ADDR(raddr), .DO(rd_data2));
RAMB4_S8 i1 (.RST(rst), .WE(wren), .EN(ram_en1), .DI(wr_data), .CLK(clk), .ADDR(raddr), .DO(rd_data1));
RAMB4_S8 i0 (.RST(rst), .WE(wren), .EN(ram_en0), .DI(wr_data), .CLK(clk), .ADDR(raddr), .DO(rd_data0));

//en_portap:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   en_porta_r  <=(0);
   else 
   en_porta_r  <=(en );

   end
//rd_data_rp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   rd_data_r  <=(0);
   else if (en_porta_r )
   rd_data_r  <=(rd_data );

   end
//append_char_ram_readp:
reg [11:0] laddrappend_char_ram_readp;
always @(rd_data7 or rd_data6 or rd_data5 or rd_data4 or rd_data3 or rd_data2 or rd_data1 or rd_data0 or rd_data_r or addr or en_porta_r )
   begin

   laddrappend_char_ram_readp=(addr );
   if (en_porta_r &(laddrappend_char_ram_readp[2:0]==0))
   rd_data  =(rd_data0 );
   else if (en_porta_r &(laddrappend_char_ram_readp[2:0]==1))
   rd_data  =(rd_data1 );
   else if (en_porta_r &(laddrappend_char_ram_readp[2:0]==2))
   rd_data  =(rd_data2 );
   else if (en_porta_r &(laddrappend_char_ram_readp[2:0]==3))
   rd_data  =(rd_data3 );
   else if (en_porta_r &(laddrappend_char_ram_readp[2:0]==4))
   rd_data  =(rd_data4 );
   else if (en_porta_r &(laddrappend_char_ram_readp[2:0]==5))
   rd_data  =(rd_data5 );
   else if (en_porta_r &(laddrappend_char_ram_readp[2:0]==6))
   rd_data  =(rd_data6 );
   else if (en_porta_r &(laddrappend_char_ram_readp[2:0]==7))
   rd_data  =(rd_data7 );
   else 
   rd_data  =(rd_data_r );

   end
//append_char_ram_combop:
reg [11:0] laddrappend_char_ram_combop,maddrappend_char_ram_combop;
always @(rst_n or en or addr )
   begin

   laddrappend_char_ram_combop=(addr );
   maddrappend_char_ram_combop=(addr );
   raddr ={maddrappend_char_ram_combop[11],maddrappend_char_ram_combop[10],maddrappend_char_ram_combop[9],maddrappend_char_ram_combop[8],maddrappend_char_ram_combop[7],maddrappend_char_ram_combop[6],maddrappend_char_ram_combop[5],maddrappend_char_ram_combop[4],maddrappend_char_ram_combop[3]};
   rst  =(!rst_n );
   ram_en0  =(en &(laddrappend_char_ram_combop[2:0]==0));
   ram_en1  =(en &(laddrappend_char_ram_combop[2:0]==1));
   ram_en2  =(en &(laddrappend_char_ram_combop[2:0]==2));
   ram_en3  =(en &(laddrappend_char_ram_combop[2:0]==3));
   ram_en4  =(en &(laddrappend_char_ram_combop[2:0]==4));
   ram_en5  =(en &(laddrappend_char_ram_combop[2:0]==5));
   ram_en6  =(en &(laddrappend_char_ram_combop[2:0]==6));
   ram_en7  =(en &(laddrappend_char_ram_combop[2:0]==7));

   end

endmodule
