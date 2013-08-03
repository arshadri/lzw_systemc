module io_ram(rst_n,clk,en_portb,wr_portb,en_porta,wr_porta,wr_datab,wr_dataa,addrb,addra,rd_datab,rd_dataa);
input rst_n;
input clk;
input en_portb;
input wr_portb;
input en_porta;
input wr_porta;
input [7:0] wr_datab;
input [7:0] wr_dataa;
input [11:0] addrb;
input [11:0] addra;
output [7:0] rd_datab;
output [7:0] rd_dataa;

reg [7:0] rd_datab;
reg [7:0] rd_dataa;

reg [8:0] raddrb;
reg [8:0] raddra;
reg rst;
reg en_portb_r;
reg en_porta_r;
reg en_b7;
reg en_b6;
reg en_b5;
reg en_b4;
reg en_b3;
reg en_b2;
reg en_b1;
reg en_b0;
reg en_a7;
reg en_a6;
reg en_a5;
reg en_a4;
reg en_a3;
reg en_a2;
reg en_a1;
reg en_a0;
wire [7:0] rd_datab7;
wire [7:0] rd_dataa7;
wire [7:0] rd_datab6;
wire [7:0] rd_dataa6;
wire [7:0] rd_datab5;
wire [7:0] rd_dataa5;
wire [7:0] rd_datab4;
wire [7:0] rd_dataa4;
wire [7:0] rd_datab3;
wire [7:0] rd_dataa3;
wire [7:0] rd_datab2;
wire [7:0] rd_dataa2;
wire [7:0] rd_datab1;
wire [7:0] rd_dataa1;
wire [7:0] rd_datab0;
wire [7:0] rd_dataa0;
reg [7:0] rd_datab_r;
reg [7:0] rd_dataa_r;

RAMB4_S8_S8 i7 (.RSTB(rst), .WEB(wr_portb), .ENB(en_b7), .DIB(wr_datab), .CLKB(clk), .ADDRB(raddrb), .RSTA(rst), .WEA(wr_porta), .ENA(en_a7), .DIA(wr_dataa), .CLKA(clk), .ADDRA(raddra), .DOB(rd_datab7), .DOA(rd_dataa7));
RAMB4_S8_S8 i6 (.RSTB(rst), .WEB(wr_portb), .ENB(en_b6), .DIB(wr_datab), .CLKB(clk), .ADDRB(raddrb), .RSTA(rst), .WEA(wr_porta), .ENA(en_a6), .DIA(wr_dataa), .CLKA(clk), .ADDRA(raddra), .DOB(rd_datab6), .DOA(rd_dataa6));
RAMB4_S8_S8 i5 (.RSTB(rst), .WEB(wr_portb), .ENB(en_b5), .DIB(wr_datab), .CLKB(clk), .ADDRB(raddrb), .RSTA(rst), .WEA(wr_porta), .ENA(en_a5), .DIA(wr_dataa), .CLKA(clk), .ADDRA(raddra), .DOB(rd_datab5), .DOA(rd_dataa5));
RAMB4_S8_S8 i4 (.RSTB(rst), .WEB(wr_portb), .ENB(en_b4), .DIB(wr_datab), .CLKB(clk), .ADDRB(raddrb), .RSTA(rst), .WEA(wr_porta), .ENA(en_a4), .DIA(wr_dataa), .CLKA(clk), .ADDRA(raddra), .DOB(rd_datab4), .DOA(rd_dataa4));
RAMB4_S8_S8 i3 (.RSTB(rst), .WEB(wr_portb), .ENB(en_b3), .DIB(wr_datab), .CLKB(clk), .ADDRB(raddrb), .RSTA(rst), .WEA(wr_porta), .ENA(en_a3), .DIA(wr_dataa), .CLKA(clk), .ADDRA(raddra), .DOB(rd_datab3), .DOA(rd_dataa3));
RAMB4_S8_S8 i2 (.RSTB(rst), .WEB(wr_portb), .ENB(en_b2), .DIB(wr_datab), .CLKB(clk), .ADDRB(raddrb), .RSTA(rst), .WEA(wr_porta), .ENA(en_a2), .DIA(wr_dataa), .CLKA(clk), .ADDRA(raddra), .DOB(rd_datab2), .DOA(rd_dataa2));
RAMB4_S8_S8 i1 (.RSTB(rst), .WEB(wr_portb), .ENB(en_b1), .DIB(wr_datab), .CLKB(clk), .ADDRB(raddrb), .RSTA(rst), .WEA(wr_porta), .ENA(en_a1), .DIA(wr_dataa), .CLKA(clk), .ADDRA(raddra), .DOB(rd_datab1), .DOA(rd_dataa1));
RAMB4_S8_S8 i0 (.RSTB(rst), .WEB(wr_portb), .ENB(en_b0), .DIB(wr_datab), .CLKB(clk), .ADDRB(raddrb), .RSTA(rst), .WEA(wr_porta), .ENA(en_a0), .DIA(wr_dataa), .CLKA(clk), .ADDRA(raddra), .DOB(rd_datab0), .DOA(rd_dataa0));

//rd_dataa_rp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   rd_dataa_r  <=(0);
   else if (en_porta_r )
   rd_dataa_r  <=(rd_dataa );

   end
//rd_datab_rp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   rd_datab_r  <=(0);
   else if (en_portb_r )
   rd_datab_r  <=(rd_datab );

   end
//en_portbp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   en_portb_r  <=(0);
   else 
   en_portb_r  <=(en_portb );

   end
//en_portap:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   en_porta_r  <=(0);
   else 
   en_porta_r  <=(en_porta );

   end
//io_ram_readbp:
reg [11:0] laddrbio_ram_readbp;
always @(rd_datab7 or rd_datab6 or rd_datab5 or rd_datab4 or rd_datab3 or rd_datab2 or rd_datab1 or rd_datab0 or rd_datab_r or addrb or en_portb_r )
   begin

   laddrbio_ram_readbp=(addrb );
   if (en_portb_r &(laddrbio_ram_readbp[2:0]==0))
   rd_datab  =(rd_datab0 );
   else if (en_portb_r &(laddrbio_ram_readbp[2:0]==1))
   rd_datab  =(rd_datab1 );
   else if (en_portb_r &(laddrbio_ram_readbp[2:0]==2))
   rd_datab  =(rd_datab2 );
   else if (en_portb_r &(laddrbio_ram_readbp[2:0]==3))
   rd_datab  =(rd_datab3 );
   else if (en_portb_r &(laddrbio_ram_readbp[2:0]==4))
   rd_datab  =(rd_datab4 );
   else if (en_portb_r &(laddrbio_ram_readbp[2:0]==5))
   rd_datab  =(rd_datab5 );
   else if (en_portb_r &(laddrbio_ram_readbp[2:0]==6))
   rd_datab  =(rd_datab6 );
   else if (en_portb_r &(laddrbio_ram_readbp[2:0]==7))
   rd_datab  =(rd_datab7 );
   else 
   rd_datab  =(rd_datab_r );

   end
//io_ram_readap:
reg [11:0] laddraio_ram_readap;
always @(rd_dataa7 or rd_dataa6 or rd_dataa5 or rd_dataa4 or rd_dataa3 or rd_dataa2 or rd_dataa1 or rd_dataa0 or rd_dataa_r or addra or en_porta_r )
   begin

   laddraio_ram_readap=(addra );
   if (en_porta_r &(laddraio_ram_readap[2:0]==0))
   rd_dataa  =(rd_dataa0 );
   else if (en_porta_r &(laddraio_ram_readap[2:0]==1))
   rd_dataa  =(rd_dataa1 );
   else if (en_porta_r &(laddraio_ram_readap[2:0]==2))
   rd_dataa  =(rd_dataa2 );
   else if (en_porta_r &(laddraio_ram_readap[2:0]==3))
   rd_dataa  =(rd_dataa3 );
   else if (en_porta_r &(laddraio_ram_readap[2:0]==4))
   rd_dataa  =(rd_dataa4 );
   else if (en_porta_r &(laddraio_ram_readap[2:0]==5))
   rd_dataa  =(rd_dataa5 );
   else if (en_porta_r &(laddraio_ram_readap[2:0]==6))
   rd_dataa  =(rd_dataa6 );
   else if (en_porta_r &(laddraio_ram_readap[2:0]==7))
   rd_dataa  =(rd_dataa7 );
   else 
   rd_dataa  =(rd_dataa_r );

   end
//io_ram_combop:
reg [11:0] laddraio_ram_combop,laddrbio_ram_combop,maddraio_ram_combop,maddrbio_ram_combop;
always @(rst_n or en_portb or en_porta or addrb or addra )
   begin

   laddraio_ram_combop=(addra );
   laddrbio_ram_combop=(addrb );
   maddraio_ram_combop=(addra );
   maddrbio_ram_combop=(addrb );
   raddra ={maddraio_ram_combop[11],maddraio_ram_combop[10],maddraio_ram_combop[9],maddraio_ram_combop[8],maddraio_ram_combop[7],maddraio_ram_combop[6],maddraio_ram_combop[5],maddraio_ram_combop[4],maddraio_ram_combop[3]};
   raddrb ={maddrbio_ram_combop[11],maddrbio_ram_combop[10],maddrbio_ram_combop[9],maddrbio_ram_combop[8],maddrbio_ram_combop[7],maddrbio_ram_combop[6],maddrbio_ram_combop[5],maddrbio_ram_combop[4],maddrbio_ram_combop[3]};
   rst  =(!rst_n );
   en_a0  =(en_porta &(laddraio_ram_combop[2:0]==0));
   en_a1  =(en_porta &(laddraio_ram_combop[2:0]==1));
   en_a2  =(en_porta &(laddraio_ram_combop[2:0]==2));
   en_a3  =(en_porta &(laddraio_ram_combop[2:0]==3));
   en_a4  =(en_porta &(laddraio_ram_combop[2:0]==4));
   en_a5  =(en_porta &(laddraio_ram_combop[2:0]==5));
   en_a6  =(en_porta &(laddraio_ram_combop[2:0]==6));
   en_a7  =(en_porta &(laddraio_ram_combop[2:0]==7));
   en_b0  =(en_portb &(laddrbio_ram_combop[2:0]==0));
   en_b1  =(en_portb &(laddrbio_ram_combop[2:0]==1));
   en_b2  =(en_portb &(laddrbio_ram_combop[2:0]==2));
   en_b3  =(en_portb &(laddrbio_ram_combop[2:0]==3));
   en_b4  =(en_portb &(laddrbio_ram_combop[2:0]==4));
   en_b5  =(en_portb &(laddrbio_ram_combop[2:0]==5));
   en_b6  =(en_portb &(laddrbio_ram_combop[2:0]==6));
   en_b7  =(en_portb &(laddrbio_ram_combop[2:0]==7));


   end

endmodule
