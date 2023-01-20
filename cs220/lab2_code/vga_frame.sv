/*******************************************************************************
 * CS220: Digital Circuit Lab
 * Computer Science Department
 * University of Crete
 * 
 * Date: 2019/XX/XX
 * Author: Your name here
 * Filename: vga_frame.sv
 * Description: Your description here
 *
 ******************************************************************************/

`timescale 1ns/1ps

module vga_frame(
  input logic clk,
  input logic rst,

  input logic i_pix_valid,
  input logic [9:0] i_col,
  input logic [9:0] i_row,

  input logic [5:0] i_player_bcol,
  input logic [5:0] i_player_brow,

  input logic [5:0] i_exit_bcol,
  input logic [5:0] i_exit_brow,

  output logic [3:0] o_red,
  output logic [3:0] o_green,
  output logic [3:0] o_blue
);

// Implement your code here
logic maze_en, maze_en_prev, check, plus1;
logic [10:0] maze_addr;
logic [15:0] maze_pixel;
logic  player_en, player_en_prev;
logic [7:0] player_addr;
logic [15:0] player_pixel;
logic exit_en, exit_en_prev;
logic [7:0] exit_addr;
logic [15:0] exit_pixel;
logic [9:0] starting_col,starting_row,starting_col2,starting_row2;

always_comb begin 
    if(player_en_prev && !exit_en_prev && !maze_en_prev) begin
        o_red = player_pixel[3:0];
        o_green = player_pixel[7:4];
        o_blue = player_pixel[11:8];
    end
    else if(!player_en_prev && exit_en_prev && !maze_en_prev) begin
        o_red = exit_pixel[3:0];
        o_green = exit_pixel[7:4];
        o_blue = exit_pixel[11:8];        
    end                                   
    else if(!player_en_prev && !exit_en_prev && maze_en_prev) begin
        o_red = maze_pixel[15:12];
        o_green = maze_pixel[11:8];
        o_blue = maze_pixel[7:4];
    end
    else begin
        o_red = 0;
        o_green = 0;
        o_blue = 0;
    end

    if(i_col / 16 == i_player_bcol && i_row / 16 == i_player_brow) begin
        player_en = 1;
        exit_en = 0;
        maze_en = 0;
        
        if(starting_col == 0 && starting_row == 0) begin
            player_addr = 0;
        end
        else if(plus1)  begin
            player_addr = 240;
        end
        else begin
            player_addr = (i_col-starting_col) + (i_row-starting_row) + ((i_row-starting_row)*15);
        end
        $display("%d",player_addr);
        $display("%d",i_col-starting_col);
        $display("%d",i_row-starting_row);
        $display("%d",starting_col);
        $display("%d",starting_row);
        $display("i_col = %d",i_col);
        $display("i_row = %d",i_row);
        $display("-----------------------------");
    end 
    else if(i_col / 16 == i_exit_bcol && i_row / 16 == i_exit_brow) begin
        player_en = 0;
        exit_en = 1;
        maze_en = 0;
        
        if(starting_col2 == 0 && starting_row2 == 0) begin
            exit_addr = 0;
        end
        else begin
            exit_addr = (i_col-starting_col2) + (i_row-starting_row2) + ((i_row-starting_row2)*15);
        end        
    end   
    else begin
        player_en = 0;
        exit_en = 0;
        maze_en = 1;
        
        maze_addr = (i_col / 16) + (i_row / 16) + ((i_col / 16)*31);
    end
end

always_ff @(posedge clk) begin
    if(rst) begin      
        maze_en_prev <= 0;
        player_en_prev <= 0;
        exit_en_prev <= 0;
        
        starting_col <= 0;
        starting_row <= 0; 
        starting_col2 <= 0;
        starting_row2 <= 0;
        
        check <= 1;
        plus1 <= 0; 
    end
    else begin
        if(i_pix_valid) begin
            if(i_col / 16 == i_player_bcol && i_row / 16 == i_player_brow) begin          
                if(starting_col == 0 && starting_row == 0) begin
                    starting_col <= i_col;
                    starting_row <= i_row;
                end
                
                if((i_col-starting_col) == 15) begin
                    check <= 0;
                end
                
                if((i_row-starting_row) > starting_row && !check) begin
                    starting_col <= i_col;
                    check <= 1;
                end
                
                if(player_addr == 239) begin
                    plus1 <= 1;
                end
                
                if(player_addr == 240) begin
                    plus1 <= 0;
                end
                
                if(player_addr == 255) begin
                    starting_row <= 0;
                    starting_col <= 0;
                end
            end           
            else if(i_col / 16 == i_exit_bcol && i_row / 16 == i_exit_brow) begin
                if(starting_col2 == 0 && starting_row2 == 0) begin
                    starting_col2 <= i_col;
                    starting_row2 <= i_row;
                end
            end
            player_en_prev <= player_en;
            exit_en_prev <= exit_en;
            maze_en_prev <= maze_en;
        end
        else begin     
            maze_en_prev <= 0;
            player_en_prev <= 0;
            exit_en_prev <= 0;           
        end
    end
end



// ROM Template Instantiation
rom #(
  .size(2048),
  .file("D:/Locker/PANEPISTIMIO/lab2_code/roms/maze1.rom") 
)
maze_rom (
  .clk(clk),
  .en(maze_en),
  .addr(maze_addr),
  .dout(maze_pixel)
);

rom #(
  .size(256),
  .file("D:/Locker/PANEPISTIMIO/lab2_code/roms/player.rom") 
)
player_rom (
  .clk(clk),
  .en(player_en),
  .addr(player_addr),
  .dout(player_pixel)
);

rom #(
  .size(256),
  .file("D:/Locker/PANEPISTIMIO/lab2_code/roms/exit.rom") 
)
exit_rom (
  .clk(clk),
  .en(exit_en),
  .addr(exit_addr),
  .dout(exit_pixel)
);


endmodule
