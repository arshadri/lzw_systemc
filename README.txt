//*****************************************************************************
// www.orahyn.com
//*****************************************************************************

This is an implemetation of an LZW encoder in SystemC which has been verified
by implementing a test bench and requisite test vectors. Only those constructs
of SystemC have been used which are synthesizabe abd recognized by the "SC2V"
converter. It has than been converted to Verilog code by using the open source 
"SC2V" program. The converted RTL is again verified in verilog simulations, and 
then verified in a Xilinx FPGA. The Digilent Spartan3 system board was used to 
verify the LZW code.

1) The doc folder contains a document which describes the LZW implementation, 
as well as the testbench implementation
 
2) The fpga_test_files folder contains the files which are downloaded into the
FPGA for compressing, through "braypp" serial port program. This is freely
available on the net.
    input test files in1.txt, in2.txt, in3.txt

3) The verilog_models folder contains the serial port model used in simulation. 
The following RAM models can be obtained from Xilinx ISE web pack for 
simulation purposes.
RAMB4_S8.v    
RAMB4_S8_S8.v
RAMB16_S18.v 
RAMB16_S18_S18.v


4) The systemc_models folder contains the serial port, model used 
in simulation, which is implemented in systemC 

5) The converted_verilog_rtl folder contains the LZW rtl files, converted from 
systemC using the SC2V open source converter. A C-Shell script "sc2v.sh" is 
present to convert all SystemC synthesizable files to Verilog format.

6) The systemc folder contains the LZW implementation files in SystemC format. 
This is synthesizable SystemC code.

7) The visual_proj contains the visual C project for running the SystemC code. 
You will need to install the requisite SystemC libraries in order to compile it

8) The run folder contains a sample "run.do" file to run the verilog 
simulations in Modelsim

9) The verilog_tb folder contains the testbench for simulation in verilog 
format, for testing the converted code.

10) The systemc_tb folder contains the testbench for simulation in SystemC 
format.

11) The verilog_test_cases contains the test files used for RTL simulations

12) The fpga_ucf_bit folder contains the UCF file for FPGA implementation, as 
well as the bit and mcs file 