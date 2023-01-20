/*******************************************************************************
 * CS220: Digital Circuits Lab
 * Computer Science Department
 * University of Crete
 * 
 * Date: 2019/10/01
 * Author: CS220 Instructors
 * Filename: counter.sv
 * Description: A simple parametric N-bit counter module with increase and
 *              overflow ports. Overflow value is parameter MAX.
 *
 ******************************************************************************/

`timescale 1ns / 1ps

module counter #(
  parameter             N = 4,
  parameter             MAX = 15
)
(
  input logic           clk,
  input logic           rst,
  
  input logic           i_increase,

  output logic [N-1: 0] o_value,
  output logic          o_overflow
);

logic [N-1:0] cnt;
logic clear_cnt;

always_ff @(posedge clk) begin
  if ( rst ) begin
    cnt <= 0;
  end
  else begin
    if ( clear_cnt ) begin
      cnt <= 0;
    end
    else if ( i_increase ) begin
      cnt <= cnt + 1;
    end
  end
end

assign clear_cnt = (cnt == MAX) & i_increase;

assign o_overflow = clear_cnt;
assign o_value = cnt;

endmodule
