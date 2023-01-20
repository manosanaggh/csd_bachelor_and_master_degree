/*******************************************************************************
 * CS220: Digital Circuits Lab
 * Computer Science Department
 * University of Crete
 * 
 * Date: 2019/10/01
 * Author: CS220 Instructors
 * Filename: lab0_top.sv
 * Description: The top module for Lab 0 that instantiates 3 counter blocks
 *
 ******************************************************************************/

`timescale 1ns / 1ps

module lab0_top (
  input  logic          clk,
  input  logic          rst,

  input  logic          i_dip,
  output logic [7:0]    o_led
);

logic timer_increase;

// increase with timer
counter #(
  .N(27),
`ifdef XILINX_SIMULATOR
  .MAX(9)
`else
  .MAX(99999999)
`endif
)
timer (
  .clk(clk),
  .rst(rst),
  .i_increase(i_dip),
  .o_value(),
  .o_overflow(timer_increase)
);

logic count_increase;
assign count_increase = timer_increase;


logic [3:0] value0;
logic [3:0] value1;
logic overflow0;
logic overflow1;
counter #(
  .N(4),
  .MAX(15)
)
cnt0 (
  .clk(clk),
  .rst(rst),
  .i_increase(count_increase),
  .o_value(value0),
  .o_overflow(overflow0)
);

counter #(
  .N(4),
  .MAX(15)
)
cnt1 (
  .clk(clk),
  .rst(rst),
  .i_increase(overflow0),
  .o_value(value1),
  .o_overflow(overflow1)
);

assign o_led = {4'b0,value0};

endmodule
