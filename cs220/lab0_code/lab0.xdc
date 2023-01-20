################################################################################
# CS220: Digital Circuits Lab
# Computer Science Department
# University of Crete
# 
# Date: 2017/10/19
# Author: CS220 Instructors
# Filename: lab0.xdc
# Description: Xilinx Design Constraint file for Lab 0 
#
################################################################################



create_clock -name clk -period 10 [get_ports clk]
set_property PACKAGE_PIN Y9 [get_ports {clk}];  # "GCLK"
set_property PACKAGE_PIN P16 [get_ports {rst}];  # "BTNC"


# ----------------------------------------------------------------------------
# User DIP Switches - Bank 35
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN F22 [get_ports {i_dip}];  # "SW0"




# ----------------------------------------------------------------------------
# User LEDS - Bank 33
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN T22 [get_ports {o_led[0]}];  # "LD0"
set_property PACKAGE_PIN T21 [get_ports {o_led[1]}];  # "LD1"
set_property PACKAGE_PIN U22 [get_ports {o_led[2]}];  # "LD2"
set_property PACKAGE_PIN U21 [get_ports {o_led[3]}];  # "LD3"
set_property PACKAGE_PIN V22 [get_ports {o_led[4]}];  # "LD4"
set_property PACKAGE_PIN W22 [get_ports {o_led[5]}];  # "LD5"
set_property PACKAGE_PIN U19 [get_ports {o_led[6]}];  # "LD6"
set_property PACKAGE_PIN U14 [get_ports {o_led[7]}];  # "LD7"



# Note that the bank voltage for IO Bank 33 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 33]];

# Set the bank voltage for IO Bank 34 to 1.8V by default.
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 34]];

# Set the bank voltage for IO Bank 35 to 1.8V by default.
set_property IOSTANDARD LVCMOS25 [get_ports -of_objects [get_iobanks 35]];

# Note that the bank voltage for IO Bank 13 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 13]];
