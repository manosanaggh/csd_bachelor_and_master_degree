################################################################################
# CS220: Digital Circuits Lab
# Computer Science Department
# University of Crete
# 
# Date: 2017/10/30
# Author: CS220 Instructors
# Filename: lab1.xdc
# Description: Xilinx Design Constraint file for Lab 1 
#
################################################################################


create_clock -name clk -period 10 [get_ports clk]
set_property PACKAGE_PIN Y9 [get_ports {clk}];  # "GCLK"
set_property PACKAGE_PIN P16 [get_ports {rst}];  # "BTNC"


# ----------------------------------------------------------------------------
# User LEDS - Bank 33
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN AA19 [get_ports {o_hsync}];  # "VGA-HS"
set_property PACKAGE_PIN Y19  [get_ports {o_vsync}];  # "VGA-VS"

set_property PACKAGE_PIN V20  [get_ports {o_red[0]}];    # "VGA-R1"
set_property PACKAGE_PIN U20  [get_ports {o_red[1]}];    # "VGA-R2"
set_property PACKAGE_PIN V19  [get_ports {o_red[2]}];    # "VGA-R3"
set_property PACKAGE_PIN V18  [get_ports {o_red[3]}];    # "VGA-R4"
set_property PACKAGE_PIN AB22 [get_ports {o_green[0]}];  # "VGA-G1"
set_property PACKAGE_PIN AA22 [get_ports {o_green[1]}];  # "VGA-G2"
set_property PACKAGE_PIN AB21 [get_ports {o_green[2]}];  # "VGA-G3"
set_property PACKAGE_PIN AA21 [get_ports {o_green[3]}];  # "VGA-G4"
set_property PACKAGE_PIN Y21  [get_ports {o_blue[0]}];   # "VGA-B1"
set_property PACKAGE_PIN Y20  [get_ports {o_blue[1]}];   # "VGA-B2"
set_property PACKAGE_PIN AB20 [get_ports {o_blue[2]}];   # "VGA-B3"
set_property PACKAGE_PIN AB19 [get_ports {o_blue[3]}];   # "VGA-B4"


# Note that the bank voltage for IO Bank 33 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 33]];

# Set the bank voltage for IO Bank 34 to 1.8V by default.
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 34]];

# Set the bank voltage for IO Bank 35 to 1.8V by default.
set_property IOSTANDARD LVCMOS25 [get_ports -of_objects [get_iobanks 35]];

# Note that the bank voltage for IO Bank 13 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 13]];
