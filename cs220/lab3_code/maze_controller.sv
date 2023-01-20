/*******************************************************************************
 * CS220: Digital Circuit Lab
 * Computer Science Department
 * University of Crete
 * 
 * Date: 2019/XX/XX
 * Author: Your name here
 * Filename: maze_controller.sv
 * Description: Your description here
 *
 ******************************************************************************/

`timescale 1ns/1ps

module maze_controller(
  input clk,
  input rst,

  input  i_control,
  input  i_up,
  input  i_down,
  input  i_left,
  input  i_right,

  output logic        o_rom_en,
  output logic [10:0] o_rom_addr,
  input  logic [15:0] i_rom_data,

  output logic [5:0] o_player_bcol,
  output logic [5:0] o_player_brow,

  input  logic [5:0] i_exit_bcol,
  input  logic [5:0] i_exit_brow,

  output logic [7:0] o_leds
);

logic pressed,up_down,finished;
logic [1:0] count_i_control;
logic [5:0] new_bcol,curr_bcol;
logic [5:0] new_brow,curr_brow;

enum logic [3:0] {
IDLE = 1,
PLAY = 2,
UP = 3,
DOWN = 4,
LEFT = 5,
RIGHT = 6,
READROM = 7,
CHECK = 8,
UPDATE = 9,
END = 10
} currentState, nextState;

always_ff @(posedge clk) begin
    if (rst) begin 
        currentState <= IDLE;
        nextState <= IDLE;
        o_player_bcol <= 1;
        o_player_brow <= 0;
        count_i_control <= 0;
        pressed <= 0;
        new_bcol <= 1;
        new_brow <= 0;
        up_down <= 0;
        curr_bcol <= 1;
        curr_brow <= 0;
        finished <= 0;
    end
    else begin
        case (currentState)
            IDLE: begin 
                if(count_i_control == 0 && !finished) begin
                    o_player_bcol <= 1;
                    o_player_brow <= 1;
                    curr_bcol <= 1;
                    curr_brow <= 0;
                end       
                if(count_i_control == 0 && finished) begin
                    o_player_bcol <= 1;
                    o_player_brow <= 0;
                    curr_bcol <= 1;
                    curr_brow <= 0;
                end  
            
                if(pressed) begin
                    count_i_control <= 0;
                    pressed <= 0;
                end
            
                if(count_i_control < 3 && i_control) begin
                    count_i_control <= count_i_control + 1;                
                end
                
                if(count_i_control == 3 && !pressed) begin
                    count_i_control <= 0;
                    nextState <= PLAY;
                end
            end
            PLAY: begin
                new_bcol <= curr_bcol;
                new_brow <= curr_brow; 
                if (i_up) begin 
                    pressed <= 1;
                    nextState <= UP;
                end
                else if(i_down) begin
                    pressed <= 1;
                    nextState <= DOWN;
                end
                else if(i_left) begin
                    pressed <= 1;
                    nextState <= LEFT;
                end
                else if(i_right) begin
                    pressed <= 1;
                    nextState <= RIGHT;                
                end
                
                if(o_player_bcol == i_exit_bcol && o_player_brow == i_exit_brow) begin
                    nextState <= END;
                end
            end
            UP: begin
               new_brow <= curr_brow - 1;
               up_down <= 1; 
               nextState <= READROM;
            end
            DOWN: begin
                new_brow <= curr_brow + 1; 
                up_down <= 1;
                nextState <= READROM;       
            end
            LEFT: begin
                new_bcol <= curr_bcol - 1; 
                up_down <= 0;
                nextState <= READROM;
            end
            RIGHT: begin
                new_bcol <= curr_bcol + 1;
                up_down <= 0;
                nextState <= READROM; 
            end
            READROM: begin
                o_rom_en <= 1;
                o_rom_addr <= new_bcol + new_brow + (new_bcol*31);
                nextState <= CHECK;
            end
            CHECK: begin
                if((i_rom_data[15:12] == 0 && i_rom_data[11:8] == 0 && i_rom_data[7:4] == 0) || new_bcol < 0 || new_brow < 0 || new_bcol > 39 || new_brow > 29) begin
                    nextState <= PLAY;
                end
                else begin
                    nextState <= UPDATE;
                end
            end
            UPDATE: begin
                if(!up_down) begin
                    curr_bcol <= new_bcol;
                    o_player_bcol <= new_bcol;
                end
                else begin
                    curr_brow <= new_brow;
                    o_player_brow <= new_brow;
                end
                nextState <= PLAY;
            end
            END: begin
                if(i_control) begin
                   finished <= 1;
                   nextState <= IDLE; 
                end
            end
            default: begin 
                nextState <= IDLE;
            end
        endcase
        currentState <= nextState;
    end
end

always_comb begin
 
end

endmodule
