/*******************************************************************************
 * CS220: Digital Circuits Lab
 * Computer Science Department
 * University of Crete
 * 
 * Date: 2019/10/01
 * Author: CS220 Instructors
 * Filename: lab0_tb.sv
 * Description: A simple testbench that generates clock and reset
 *
 ******************************************************************************/

`timescale 1ns/1ps

// Only for Icarus Verilog
//`define VCD_WAVES

// CLK 10 ns -> 100 MHz
`define CLK_PERIOD 10
`define SIM_CYCLES 1000

module lab0_tb;

logic clk;
logic rst;

always #(`CLK_PERIOD/2) clk = ~clk;

logic dip = 1;
logic [7:0] led;

lab0_top uut (
  .clk(clk),
  .rst(rst),

  .i_dip(dip),
  .o_led(led)
);

// clk and reset
initial begin
`ifdef VCD_WAVES
  $dumpfile("tb_waves.vcd");
  $dumpvars;
`endif

  clk = 0;
  rst = 1;
  @(posedge clk);
  @(posedge clk);
  @(posedge clk);
  #1;
  rst = 0;
  @(posedge clk);


  repeat (`SIM_CYCLES) @(posedge clk);
  #1;
  $finish;
end

endmodule
