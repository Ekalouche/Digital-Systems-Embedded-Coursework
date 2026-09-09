-- Copyright (C) 2018  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and its AMPP partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 18.1.0 Build 625 09/12/2018 SJ Standard Edition"

-- DATE "10/07/2025 18:51:07"

-- 
-- Device: Altera 5CEBA4F23C7 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY ALTERA_LNSIM;
LIBRARY CYCLONEV;
LIBRARY IEEE;
USE ALTERA_LNSIM.ALTERA_LNSIM_COMPONENTS.ALL;
USE CYCLONEV.CYCLONEV_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	Comp1Exam IS
    PORT (
	D : IN std_logic;
	E : IN std_logic;
	F : IN std_logic;
	X : BUFFER std_logic
	);
END Comp1Exam;

-- Design Ports Information
-- X	=>  Location: PIN_M18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- E	=>  Location: PIN_N19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- F	=>  Location: PIN_M22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- D	=>  Location: PIN_L22,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF Comp1Exam IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_D : std_logic;
SIGNAL ww_E : std_logic;
SIGNAL ww_F : std_logic;
SIGNAL ww_X : std_logic;
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \F~input_o\ : std_logic;
SIGNAL \D~input_o\ : std_logic;
SIGNAL \E~input_o\ : std_logic;
SIGNAL \X~0_combout\ : std_logic;
SIGNAL \ALT_INV_D~input_o\ : std_logic;
SIGNAL \ALT_INV_F~input_o\ : std_logic;
SIGNAL \ALT_INV_E~input_o\ : std_logic;

BEGIN

ww_D <= D;
ww_E <= E;
ww_F <= F;
X <= ww_X;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\ALT_INV_D~input_o\ <= NOT \D~input_o\;
\ALT_INV_F~input_o\ <= NOT \F~input_o\;
\ALT_INV_E~input_o\ <= NOT \E~input_o\;

-- Location: IOOBUF_X54_Y19_N22
\X~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \X~0_combout\,
	devoe => ww_devoe,
	o => ww_X);

-- Location: IOIBUF_X54_Y19_N38
\F~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_F,
	o => \F~input_o\);

-- Location: IOIBUF_X54_Y19_N55
\D~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_D,
	o => \D~input_o\);

-- Location: IOIBUF_X54_Y19_N4
\E~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_E,
	o => \E~input_o\);

-- Location: LABCELL_X53_Y19_N0
\X~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \X~0_combout\ = ( \E~input_o\ & ( \F~input_o\ ) ) # ( !\E~input_o\ & ( !\D~input_o\ ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1111000011110000001100110011001111110000111100000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \ALT_INV_F~input_o\,
	datac => \ALT_INV_D~input_o\,
	datae => \ALT_INV_E~input_o\,
	combout => \X~0_combout\);

-- Location: LABCELL_X19_Y35_N3
\~QUARTUS_CREATED_GND~I\ : cyclonev_lcell_comb
-- Equation(s):

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
;
END structure;


