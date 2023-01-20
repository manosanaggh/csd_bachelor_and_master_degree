/*******************************************************************************
 * CS220: Digital Circuit Lab
 * Computer Science Department
 * University of Crete
 * 
 * Date: 2019/XX/XX
 * Author: Your name here
 * Filename: vga_sync.sv
 * Description: Implements VGA HSYNC and VSYNC timings for 640 x 480 @ 60Hz
 *
 ******************************************************************************/

`timescale 1ns/1ps

module vga_sync(
  input logic clk,
  input logic rst,

  output logic o_pix_valid,
  output logic [9:0] o_col,
  output logic [9:0] o_row,

  output logic o_hsync,
  output logic o_vsync
);


parameter FRAME_HPIXELS           = 640;
parameter FRAME_HFPORCH           = 16;
parameter FRAME_HSPULSE           = 96;
parameter FRAME_HBPORCH           = 48;
parameter FRAME_MAX_HCOUNT        = 800;

parameter FRAME_VLINES            = 480;
parameter FRAME_VFPORCH           = 10;
parameter FRAME_VSPULSE           = 2;
parameter FRAME_VBPORCH           = 29;
parameter FRAME_MAX_VCOUNT        = 521;

logic [9:0] hcnt;
logic [9:0] o_mux2_1;
logic hcnt_clr;
logic hs_set;
logic hs_clr;
logic o_and1;
logic hsync;
logic hsync_delay;
logic [9:0] vcnt;
logic vcnt_clear;
logic vs_set;
logic vs_clr;
logic o_and2;
logic vsync;

// Implement your code here
always_ff @(posedge clk) begin
    if(rst) begin
        hcnt <= 0;
        hsync <= 0;
        hsync_delay <= 0;
    end
    else begin
        hcnt <= o_mux2_1;
        hsync <= o_and1;
        hsync_delay <= hsync;
    end
end

always_ff @(posedge clk) begin
    if(rst) begin
        vcnt <= 0;
    end
    else begin
        if(vcnt_clear) begin
            vcnt <= 0;
        end
        else begin
            if(hcnt_clr) begin
                vcnt <= vcnt + 1;
            end
            else begin
                vcnt <= vcnt;
            end
        end
    end
end

always_ff @(posedge clk) begin
    if(rst) begin
        vsync <= 0;
    end
    else begin
        vsync <= o_and2;
    end
end

always_comb begin
    hcnt_clr = (hcnt == FRAME_MAX_HCOUNT-1);
    o_mux2_1 = (hcnt_clr) ? 0 : (hcnt + 1);
    hs_set = (hcnt == FRAME_HPIXELS+FRAME_HFPORCH-1);
    hs_clr = (hcnt == FRAME_HPIXELS+FRAME_HFPORCH+FRAME_HSPULSE-1);
    o_and1 = ((hs_set | hsync) & (~hs_clr));
    o_hsync = ~hsync_delay;
    o_col = hcnt;
    o_pix_valid = ((hcnt < FRAME_HPIXELS) & (vcnt < FRAME_VLINES ));
    o_row = vcnt;
    vcnt_clear = (hcnt_clr & (FRAME_MAX_VCOUNT-1 == vcnt));
    vs_set = (hcnt_clr & (FRAME_VLINES+FRAME_VFPORCH-1 == vcnt));
    vs_clr = (hcnt_clr & (FRAME_VLINES+FRAME_VFPORCH+FRAME_VSPULSE-1 == vcnt));
    o_and2 = ((vs_set | vsync) & (~vs_clr));
    o_vsync = ~vsync;
end

endmodule
