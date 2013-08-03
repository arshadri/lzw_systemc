module hashl(rst_n,clk,mux_code_val,shift_char,recal_hash,gen_hash,prefix_data,append_data,string_data,char_in,in_code_mem,collis,match,not_in_mem,string_reg,addr);
input rst_n;
input clk;
input mux_code_val;
input shift_char;
input recal_hash;
input gen_hash;
input [12:0] prefix_data;
input [7:0] append_data;
input [12:0] string_data;
input [7:0] char_in;
output in_code_mem;
output collis;
output match;
output not_in_mem;
output [12:0] string_reg;
output [12:0] addr;

reg in_code_mem;
reg collis;
reg match;
reg not_in_mem;
reg [12:0] string_reg;
reg [12:0] addr;

reg [11:0] addr_saves;
reg cmp_prefix_data;
reg cmp_append_char;
reg [12:0] index;
reg gen_hash_ss;
reg gen_hash_s;
reg [12:0] addr_save;


//addrp:
reg [12:0] addrlsaddrp;
always @(addr_save )
   begin

   addrlsaddrp=(addr_save );
   addr_saves ={addrlsaddrp[11],addrlsaddrp[10],addrlsaddrp[9],addrlsaddrp[8],addrlsaddrp[7],addrlsaddrp[6],addrlsaddrp[5],addrlsaddrp[4],addrlsaddrp[3],addrlsaddrp[2],addrlsaddrp[1],addrlsaddrp[0]};

   end
//recalhashp:
always @(index or addr_saves or recal_hash )
   begin

   if (recal_hash )
   addr  =({1'b0,addr_saves +12});
   else 
   addr  =(index );

   end
//stringregp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   string_reg  <=(0);
   else if (shift_char )
   string_reg  <=(mux_code_val ?string_data :{5'h0,char_in[7:0]});

   end
//indexp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   index  <=(0);
   else if (gen_hash )
   index  <=((char_in <<5)^string_reg );

   end
//addrsavep:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   addr_save  <=(0);
   else 
   addr_save  <=(index );

   end
//genhashssp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   gen_hash_ss  <=(0);
   else 
   gen_hash_ss  <=(gen_hash_s );

   end
//genhashp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   gen_hash_s  <=(0);
   else 
   gen_hash_s  <=(gen_hash );

   end
//collisp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   collis  <=(0);
   else if (gen_hash )
   collis  <=(0);
   else if (gen_hash_ss )
   collis  <=((cmp_append_char &~cmp_prefix_data )
|(~   cmp_append_char &cmp_prefix_data ));

   end
//matchp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   match  <=(0);
   else if (gen_hash )
   match  <=(0);
   else if (gen_hash_ss )
   match  <=(cmp_append_char &cmp_prefix_data );

   end
//in_code_memp:
always @(negedge rst_n or posedge clk )
   begin

   if (!rst_n )
   in_code_mem  <=(0);
   else if (gen_hash )
   in_code_mem  <=(0);
   else if (gen_hash_ss )
   in_code_mem  <=((string_data !='h1FFF ));

   end
//hashl_combo:
always @(string_reg or prefix_data or char_in or append_data or gen_hash_ss or string_data )
   begin

   not_in_mem  =((string_data =='h1FFF )&gen_hash_ss );
   cmp_append_char  =(append_data ==char_in );
   cmp_prefix_data  =(prefix_data ==string_reg );

   end

endmodule
