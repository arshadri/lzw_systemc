module lzw(rst,clk66,rx,valid_start_deb,pwr_up,final_done,lzw_done,done_cr,init_lzw,init_cr,ser_recv_done,tx);
input rst;
input clk66;
input rx;
output valid_start_deb;
output pwr_up;
output final_done;
output lzw_done;
output done_cr;
output init_lzw;
output init_cr;
output ser_recv_done;
output tx;


wire [7:0] dummy1;
wire [7:0] drive0_8bit;
wire drive0;
wire rst_n;
wire clk;
wire start_xmt;
wire lzw_done_out;
wire init_lzw_out;
wire done_cr_out;
wire init_cr_out;
wire xmt_done;
wire rcv_done;
wire ena_outram;
wire enb_ioram;
wire web_ioram;
wire ena_ioram;
wire wea_ioram;
wire [11:0] char_cnt;
wire [11:0] outram_cnt;
wire [11:0] addra_outram;
wire [11:0] addrb_ioram;
wire [11:0] addra_ioram;
wire [7:0] xmt_byte;
wire [7:0] char_in;
wire [7:0] lzw_byte;
wire [7:0] rcv_byte;

io_ram io_ram2 (.rst_n(rst_n), .clk(clk), .wr_datab(drive0_8bit), .addrb(addrb_ioram), .en_portb(enb_ioram), .wr_portb(drive0), .wr_dataa(rcv_byte), .addra(addra_ioram), .en_porta(ena_ioram), .wr_porta(wea_ioram), .rd_datab(char_in), .rd_dataa(dummy1));
lzw_enc lzw_enc1 (.rst_n(rst_n), .clk(clk), .char_in(char_in), .char_cnt(char_cnt), .init_lzw(init_lzw), .init_cr(init_cr), .ena_outram(ena_outram), .addra_outram(addra_outram), .outram_cnt(outram_cnt), .done_cr(done_cr), .lzw_done(lzw_done), .addrb_ioram(addrb_ioram), .enb_ioram(enb_ioram), .web_ioram(web_ioram), .xmt_byte(xmt_byte));
top_ctrl top_ctrl1 (.rst_n(rst_n), .clk(clk), .char_in(rcv_byte), .xmt_done(xmt_done), .rcv_done(rcv_done), .outram_cnt(outram_cnt), .lzw_done(lzw_done), .done_cr(done_cr), .pwr_up(pwr_up), .final_done(final_done), .lzw_done_out(lzw_done_out), .init_lzw_out(init_lzw_out), .done_cr_out(done_cr_out), .init_cr_out(init_cr_out), .ser_recv_done(ser_recv_done), .ena_outram(ena_outram), .addra_outram(addra_outram), .wea_ioram(wea_ioram), .ena_ioram(ena_ioram), .addra_ioram(addra_ioram), .start_xmt(start_xmt), .char_cnt(char_cnt), .init_lzw(init_lzw), .init_cr(init_cr));
ser ser1 (.rst_n(rst_n), .clk(clk), .xmt_byte(xmt_byte), .start_xmt(start_xmt), .sin(rx), .vld_str_deb(valid_start_deb), .xmt_done(xmt_done), .rcv_done(rcv_done), .rcv_byte(rcv_byte), .sout(tx));
clk_rst clk_rst1 (.rst(rst), .clk66(clk66), .drive0_8bit(drive0_8bit), .drive0(drive0), .rst_n(rst_n), .clk(clk));


endmodule
