module clk_rst(rst,clk66,drive0_8bit,drive0,rst_n,clk);
input rst;
input clk66;
output [7:0] drive0_8bit;
output drive0;
output rst_n;
output clk;

wire [7:0] drive0_8bit;
wire drive0;
reg rst_n;
reg clk;

reg rst_s;

//synopsys translate_off
initial clk =0;
//synopsys translate_on
//clkp:
always @(posedge clk66 )
   begin

   clk  <=(!clk );

   end
//rstp:
always @(posedge rst or posedge clk )
   begin

   if (rst )
      begin

      rst_s  <=(0);
      rst_n  <=(0);

      end

   else 
      begin

      rst_s  <=(1);
      rst_n  <=(rst_s );

      end


   end
//combop:

   assign drive0  =(0);
   assign drive0_8bit  =(0);
   
endmodule
