  
  vlog ../verilog_test_cases/test.v \
       ../verilog_tb/tb.v \
       ../converted_verilog_rtl/timescale.v \
       ../converted_verilog_rtl/lzw.v \
       ../converted_verilog_rtl/lzw_ctrl.v \
       ../converted_verilog_rtl/lzw_enc.v \
       ../converted_verilog_rtl/top_ctrl.v \
       ../converted_verilog_rtl/code_value_ram.v \
       ../converted_verilog_rtl/hashl.v \
       ../converted_verilog_rtl/dictionary_ram.v \
       ../converted_verilog_rtl/ser.v \
       ../converted_verilog_rtl/io_ram.v \
       ../converted_verilog_rtl/prefix_code_ram.v \
       ../converted_verilog_rtl/append_char_ram.v \
       ../converted_verilog_rtl/outreg.v \
       ../converted_verilog_rtl/clk_rst.v \
       ../verilog_models/ser_model.v \
       ../verilog_models/RAMB4_S8.v \
       ../verilog_models/RAMB4_S8_S8.v \
       ../verilog_models/RAMB16_S18.v \
       ../verilog_models/RAMB16_S18_S18.v
  
  vsim work.test
  do wave2.do
  run -all