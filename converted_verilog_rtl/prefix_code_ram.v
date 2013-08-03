module prefix_code_ram(rst_n,clk,en,wren,wr_data,addr,rd_data);
input rst_n;
input clk;
input en;
input wren;
input [12:0] wr_data;
input [11:0] addr;
output [12:0] rd_data;

reg [12:0] rd_data;

reg [15:0] wrdatac;
wire [1:0] dummy3;
wire [1:0] dummy2;
wire [1:0] dummy1;
wire [1:0] dummy0;
reg [2:0] drive0_3;
reg [1:0] drive0_2;
reg [9:0] raddr;
reg rst;
reg en_porta_r;
reg ram_en3;
reg ram_en2;
reg ram_en1;
reg ram_en0;
wire [15:0] rd_data3;
wire [15:0] rd_data2;
wire [15:0] rd_data1;
wire [15:0] rd_data0;
reg [12:0] rd_data_r;

RAMB16_S18 i3 (.SSR(rst), .WE(wren), .EN(ram_en3), .DIP(drive0_2), .DI(wrdatac), .CLK(clk), .ADDR(raddr), .DOP(dummy3), .DO(rd_data3));
RAMB16_S18 i2 (.SSR(rst), .WE(wren), .EN(ram_en2), .DIP(drive0_2), .DI(wrdatac), .CLK(clk), .ADDR(raddr), .DOP(dummy2), .DO(rd_data2));
RAMB16_S18 i1 (.SSR(rst), .WE(wren), .EN(ram_en1), .DIP(drive0_2), .DI(wrdatac), .CLK(clk), .ADDR(raddr), .DOP(dummy1), .DO(rd_data1));
RAMB16_S18 i0 (.SSR(rst), .WE(wren), .EN(ram_en0), .DIP(drive0_2), .DI(wrdatac), .CLK(clk), .ADDR(raddr), .DOP(dummy0), .DO(rd_data0));

//rd_data_rp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   rd_data_r  <=(0);
   else if (en_porta_r )
   rd_data_r  <=(rd_data );

   end
//en_portap:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   en_porta_r  <=(0);
   else 
   en_porta_r  <=(en );

   end
//prefix_code_ram_readp:
reg [11:0] laddrprefix_code_ram_readp;
always @(rd_data3 or rd_data2 or rd_data1 or rd_data0 or rd_data_r or addr or en_porta_r )
   begin

   laddrprefix_code_ram_readp=(addr );
   if (en_porta_r &(laddrprefix_code_ram_readp[1:0]==0))
   rd_data  =(rd_data0 );
   else if (en_porta_r &(laddrprefix_code_ram_readp[1:0]==1))
   rd_data  =(rd_data1 );
   else if (en_porta_r &(laddrprefix_code_ram_readp[1:0]==2))
   rd_data  =(rd_data2 );
   else if (en_porta_r &(laddrprefix_code_ram_readp[1:0]==3))
   rd_data  =(rd_data3 );
   else 
   rd_data  =(rd_data_r );

   end
//prefix_code_ram_combop:
reg [11:0] laddrprefix_code_ram_combop,maddrprefix_code_ram_combop;
always @(wr_data or rst_n or en or addr )
   begin

   laddrprefix_code_ram_combop=(addr );
   maddrprefix_code_ram_combop=(addr );
   raddr ={maddrprefix_code_ram_combop[11],maddrprefix_code_ram_combop[10],maddrprefix_code_ram_combop[9],maddrprefix_code_ram_combop[8],maddrprefix_code_ram_combop[7],maddrprefix_code_ram_combop[6],maddrprefix_code_ram_combop[5],maddrprefix_code_ram_combop[4],maddrprefix_code_ram_combop[3],maddrprefix_code_ram_combop[2]};
   rst  =(!rst_n );
   ram_en0  =(en &(laddrprefix_code_ram_combop[1:0]==0));
   ram_en1  =(en &(laddrprefix_code_ram_combop[1:0]==1));
   ram_en2  =(en &(laddrprefix_code_ram_combop[1:0]==2));
   ram_en3  =(en &(laddrprefix_code_ram_combop[1:0]==3));
   drive0_2  =(0);
   drive0_3  =(0);
   wrdatac  ={3'h0,wr_data[12:0]};

   end

endmodule
