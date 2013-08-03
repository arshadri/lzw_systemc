module code_value_ram(rst_n,clk,en_portb,wr_portb,en_porta,wr_porta,wr_datab,wr_dataa,addrb,addra,rd_dataa);
input rst_n;
input clk;
input en_portb;
input wr_portb;
input en_porta;
input wr_porta;
input [12:0] wr_datab;
input [12:0] wr_dataa;
input [12:0] addrb;
input [12:0] addra;
output [12:0] rd_dataa;

reg [12:0] rd_dataa;

reg [15:0] wr_databc;
reg [15:0] wr_dataac;
wire [15:0] ddummy3;
wire [15:0] ddummy2;
wire [15:0] ddummy1;
wire [15:0] ddummy0;
reg [2:0] drive0_3;
reg [9:0] raddrb;
reg [9:0] raddra;
reg rst;
reg en_a3;
reg en_a2;
reg en_a1;
reg en_a0;
reg en_porta_r;
wire [15:0] rd_dataa3;
wire [15:0] rd_dataa2;
wire [15:0] rd_dataa1;
wire [15:0] rd_dataa0;
reg [12:0] rd_dataa_r;

RAMB16_S18_S18 i3 (.DIPA(2'b00), .DIPB(2'b00), .SSRB(rst), .WEB(wr_portb), .ENB(en_portb), .DIB(wr_databc), .CLKB(clk), .ADDRB(raddrb), .SSRA(rst), .WEA(wr_porta), .ENA(en_a3), .DIA(wr_dataac), .CLKA(clk), .ADDRA(raddra), .DOB(ddummy3), .DOA(rd_dataa3));
RAMB16_S18_S18 i2 (.DIPA(2'b00), .DIPB(2'b00), .SSRB(rst), .WEB(wr_portb), .ENB(en_portb), .DIB(wr_databc), .CLKB(clk), .ADDRB(raddrb), .SSRA(rst), .WEA(wr_porta), .ENA(en_a2), .DIA(wr_dataac), .CLKA(clk), .ADDRA(raddra), .DOB(ddummy2), .DOA(rd_dataa2));
RAMB16_S18_S18 i1 (.DIPA(2'b00), .DIPB(2'b00), .SSRB(rst), .WEB(wr_portb), .ENB(en_portb), .DIB(wr_databc), .CLKB(clk), .ADDRB(raddrb), .SSRA(rst), .WEA(wr_porta), .ENA(en_a1), .DIA(wr_dataac), .CLKA(clk), .ADDRA(raddra), .DOB(ddummy1), .DOA(rd_dataa1));
RAMB16_S18_S18 i0 (.DIPA(2'b00), .DIPB(2'b00), .SSRB(rst), .WEB(wr_portb), .ENB(en_portb), .DIB(wr_databc), .CLKB(clk), .ADDRB(raddrb), .SSRA(rst), .WEA(wr_porta), .ENA(en_a0), .DIA(wr_dataac), .CLKA(clk), .ADDRA(raddra), .DOB(ddummy0), .DOA(rd_dataa0));

//rd_dataa_rp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   rd_dataa_r  <=(0);
   else if (en_porta_r )
   rd_dataa_r  <=(rd_dataa );

   end
//en_portap:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   en_porta_r  <=(0);
   else 
   en_porta_r  <=(en_porta );

   end
//code_value_ram_readap:
reg [12:0] laddracode_value_ram_readap;
always @(rd_dataa3 or rd_dataa2 or rd_dataa1 or rd_dataa0 or rd_dataa_r or addra or en_porta_r )
   begin

   laddracode_value_ram_readap=(addra );
   if (en_porta_r &(laddracode_value_ram_readap[1:0]==0))
   rd_dataa  =(rd_dataa0 );
   else if (en_porta_r &(laddracode_value_ram_readap[1:0]==1))
   rd_dataa  =(rd_dataa1 );
   else if (en_porta_r &(laddracode_value_ram_readap[1:0]==2))
   rd_dataa  =(rd_dataa2 );
   else if (en_porta_r &(laddracode_value_ram_readap[1:0]==3))
   rd_dataa  =(rd_dataa3 );
   else 
   rd_dataa  =(rd_dataa_r );

   end
//code_value_ram_combop:
reg [12:0] laddracode_value_ram_combop,maddracode_value_ram_combop,maddrbcode_value_ram_combop;
always @(wr_datab or wr_dataa or rst_n or en_porta or addrb or addra )
   begin

   laddracode_value_ram_combop=(addra );
   maddracode_value_ram_combop=(addra );
   maddrbcode_value_ram_combop=(addrb );
   raddra ={maddracode_value_ram_combop[11],maddracode_value_ram_combop[10],maddracode_value_ram_combop[9],maddracode_value_ram_combop[8],maddracode_value_ram_combop[7],maddracode_value_ram_combop[6],maddracode_value_ram_combop[5],maddracode_value_ram_combop[4],maddracode_value_ram_combop[3],maddracode_value_ram_combop[2]};
   raddrb ={maddrbcode_value_ram_combop[9],maddrbcode_value_ram_combop[8],maddrbcode_value_ram_combop[7],maddrbcode_value_ram_combop[6],maddrbcode_value_ram_combop[5],maddrbcode_value_ram_combop[4],maddrbcode_value_ram_combop[3],maddrbcode_value_ram_combop[2],maddrbcode_value_ram_combop[1],maddrbcode_value_ram_combop[0]};
   rst  =(!rst_n );
   en_a0  =(en_porta &(laddracode_value_ram_combop[1:0]==0));
   en_a1  =(en_porta &(laddracode_value_ram_combop[1:0]==1));
   en_a2  =(en_porta &(laddracode_value_ram_combop[1:0]==2));
   en_a3  =(en_porta &(laddracode_value_ram_combop[1:0]==3));
   drive0_3  =(0);
   wr_dataac ={3'h0,wr_dataa[12:0]};
   wr_databc ={3'h0,wr_datab[12:0]};

   end

endmodule
