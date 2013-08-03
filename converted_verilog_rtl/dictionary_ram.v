module dictionary_ram(rst_n,clk,wea_pcram,wea_acram,string_data,addr,char_data,append_data,prefix_data);
input rst_n;
input clk;
input wea_pcram;
input wea_acram;
input [12:0] string_data;
input [12:0] addr;
input [7:0] char_data;
output [7:0] append_data;
output [12:0] prefix_data;


reg [11:0] raddr;
reg drive_1;

append_char_ram append_char_ram1 (.rst_n(rst_n), .clk(clk), .wr_data(char_data), .addr(raddr), .en(drive_1), .wren(wea_acram), .rd_data(append_data));
prefix_code_ram prefix_code_ram1 (.rst_n(rst_n), .clk(clk), .wr_data(string_data), .addr(raddr), .en(drive_1), .wren(wea_pcram), .rd_data(prefix_data));

//combo_dictp:
reg [12:0] laddrcombo_dictp;
always @(addr )
   begin

   laddrcombo_dictp=(addr );
   raddr ={laddrcombo_dictp[11],laddrcombo_dictp[10],laddrcombo_dictp[9],laddrcombo_dictp[8],laddrcombo_dictp[7],laddrcombo_dictp[6],laddrcombo_dictp[5],laddrcombo_dictp[4],laddrcombo_dictp[3],laddrcombo_dictp[2],laddrcombo_dictp[1],laddrcombo_dictp[0]};
   drive_1  =(1);

   end

endmodule
