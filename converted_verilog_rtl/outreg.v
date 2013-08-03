module outreg(rst_n,clk,read_data,write_sp,write_data,prefix_data,tc_outreg,valid_dcnt,lzw_byte);
input rst_n;
input clk;
input read_data;
input write_sp;
input write_data;
input [12:0] prefix_data;
output tc_outreg;
output valid_dcnt;
output [7:0] lzw_byte;

reg tc_outreg;
reg valid_dcnt;
reg [7:0] lzw_byte;

reg [31:0] shift_reg;
reg [4:0] datain_cnt;
reg flush;


//datain_cntp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   datain_cnt  <=(0);
   else if (flush )
   datain_cnt  <=(0);
   else 
      begin

      if (read_data &!write_data &!write_sp )
      datain_cnt  <=(datain_cnt -8);
      else if (!read_data &write_data &!write_sp )
      datain_cnt  <=(datain_cnt +13);
      else if (!read_data &!write_data &write_sp )
      datain_cnt  <=(datain_cnt +13);
      else 
      datain_cnt  <=(datain_cnt );

      end


   end
//shift_regp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   shift_reg  <=(0);
   else if (write_data )
   shift_reg  <=(shift_reg |(prefix_data <<(19-datain_cnt )));
   else if (write_sp )
   shift_reg  <=(shift_reg | ( 'h1fff<< (19-datain_cnt )));//((19-datain_cnt )<<'h1fff )); //(0x1 fff <<(19 - datain_cnt .read ()))) ;
   else if (read_data )
   shift_reg  <=(shift_reg <<8);

   end
//outreg_combop:
always @(shift_reg or datain_cnt or read_data )
   begin

   flush  =(read_data &(datain_cnt <8));
   tc_outreg  =(datain_cnt ==0);
   valid_dcnt  =(datain_cnt >=8);
   lzw_byte  =(shift_reg >>24);

   end

endmodule
