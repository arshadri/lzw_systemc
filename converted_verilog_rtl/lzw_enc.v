module lzw_enc(rst_n,clk,ena_outram,init_lzw,init_cr,char_in,addra_outram,char_cnt,done_cr,lzw_done,enb_ioram,web_ioram,outram_cnt,addrb_ioram,xmt_byte);
input rst_n;
input clk;
input ena_outram;
input init_lzw;
input init_cr;
input [7:0] char_in;
input [11:0] addra_outram;
input [11:0] char_cnt;
output done_cr;
output lzw_done;
output enb_ioram;
output web_ioram;
output [11:0] outram_cnt;
output [11:0] addrb_ioram;
output [7:0] xmt_byte;


wire [7:0] dummy0;
reg [12:0] drive1_13bit;
reg [7:0] drive0_8bit;
reg drive0;
wire read_data;
wire valid_dcnt;
wire write_sp;
wire web_outram;
wire hash;
wire collis;
wire match;
wire tc_outreg;
wire mux_code_val;
wire write_data;
wire wea_pcram;
wire wea_acram;
wire inc_cvadata;
wire wea_cvram;
wire ena_cvram;
wire recal_hash;
wire gen_hash;
wire shift_char;
wire web_cvram;
wire enb_cvram;
wire done_lzw;
wire enb_outram;
wire wrb_outram;
wire [11:0] addrb_outram;
wire [7:0] lzw_byte;
wire [12:0] string_reg;
wire [12:0] wr_cvdataa;
wire [12:0] addrb_cvram;
wire in_code_mem;
wire not_in_mem;
wire [12:0] string_data;
wire [12:0] addr;
wire [7:0] append_data;
wire [12:0] prefix_data;

io_ram outram (.rst_n(rst_n), .clk(clk), .wr_datab(lzw_byte), .addrb(addrb_outram), .en_portb(enb_outram), .wr_portb(web_outram), .wr_dataa(drive0_8bit), .addra(addra_outram), .en_porta(ena_outram), .wr_porta(drive0), .rd_datab(dummy0), .rd_dataa(xmt_byte));
outreg outreg1 (.rst_n(rst_n), .clk(clk), .prefix_data(prefix_data), .read_data(read_data), .write_sp(write_sp), .write_data(write_data), .lzw_byte(lzw_byte), .tc_outreg(tc_outreg), .valid_dcnt(valid_dcnt));
lzw_ctrl lzw_ctrl1 (.rst_n(rst_n), .clk(clk), .in_code_mem(in_code_mem), .collis(collis), .match(match), .not_in_mem(not_in_mem), .char_cnt(char_cnt), .init_lzw(init_lzw), .init_cr(init_cr), .tc_outreg(tc_outreg), .valid_dcnt(valid_dcnt), .outram_cnt(outram_cnt), .mux_code_val(mux_code_val), .shift_char(shift_char), .write_sp(write_sp), .read_data(read_data), .write_data(write_data), .wea_pcram(wea_pcram), .wea_acram(wea_acram), .wea_cvram(wea_cvram), .ena_cvram(ena_cvram), .wr_cvdataa(wr_cvdataa), .web_cvram(web_cvram), .enb_cvram(enb_cvram), .addrb_cvram(addrb_cvram), .web_outram(web_outram), .enb_outram(enb_outram), .addrb_outram(addrb_outram), .web_ioram(web_ioram), .enb_ioram(enb_ioram), .addrb_ioram(addrb_ioram), .recal_hash(recal_hash), .gen_hash(gen_hash), .lzw_done(lzw_done), .done_cr(done_cr));
hashl hash1 (.rst_n(rst_n), .clk(clk), .prefix_data(prefix_data), .append_data(append_data), .string_data(string_data), .char_in(char_in), .mux_code_val(mux_code_val), .shift_char(shift_char), .recal_hash(recal_hash), .gen_hash(gen_hash), .in_code_mem(in_code_mem), .collis(collis), .match(match), .not_in_mem(not_in_mem), .string_reg(string_reg), .addr(addr));
code_value_ram code_value_ram1 (.rst_n(rst_n), .clk(clk), .wr_datab(drive1_13bit), .addrb(addrb_cvram), .en_portb(enb_cvram), .wr_portb(web_cvram), .wr_dataa(wr_cvdataa), .addra(addr), .en_porta(ena_cvram), .wr_porta(wea_cvram), .rd_dataa(string_data));
dictionary_ram dictionary_ram1 (.rst_n(rst_n), .clk(clk), .string_data(string_reg), .char_data(char_in), .addr(addr), .wea_pcram(wea_pcram), .wea_acram(wea_acram), .append_data(append_data), .prefix_data(prefix_data));

//combo_lzwencp:
always @(rst_n )
   begin

   drive0  =(0);
   drive0_8bit  =(0);
   drive1_13bit  =('h1fff );

   end

endmodule
