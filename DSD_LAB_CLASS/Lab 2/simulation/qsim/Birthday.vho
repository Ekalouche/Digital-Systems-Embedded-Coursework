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

-- DATE "09/15/2025 19:45:47"

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

ENTITY 	birthday IS
    PORT (
	W : IN std_logic;
	X : IN std_logic;
	Y : IN std_logic;
	Z : IN std_logic;
	g : OUT std_logic;
	f : OUT std_logic;
	e : OUT std_logic;
	d : OUT std_logic;
	c : OUT std_logic;
	b : OUT std_logic;
	a : OUT std_logic;
	a_cond : OUT std_logic;
	b_cond : OUT std_logic;
	c_cond : OUT std_logic;
	d_cond : OUT std_logic;
	e_cond : OUT std_logic;
	f_cond : OUT std_logic;
	g_cond : OUT std_logic;
	a_sel : OUT std_logic;
	b_sel : OUT std_logic;
	c_sel : OUT std_logic;
	d_sel : OUT std_logic;
	e_sel : OUT std_logic;
	f_sel : OUT std_logic;
	g_sel : OUT std_logic
	);
END birthday;

-- Design Ports Information
-- g	=>  Location: PIN_AA22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- f	=>  Location: PIN_Y21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- e	=>  Location: PIN_Y22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- d	=>  Location: PIN_W21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- c	=>  Location: PIN_W22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b	=>  Location: PIN_V21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a	=>  Location: PIN_U21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a_cond	=>  Location: PIN_AA20,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b_cond	=>  Location: PIN_AB20,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- c_cond	=>  Location: PIN_AA19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- d_cond	=>  Location: PIN_AA18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- e_cond	=>  Location: PIN_AB18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- f_cond	=>  Location: PIN_AA17,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- g_cond	=>  Location: PIN_U22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- a_sel	=>  Location: PIN_Y19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- b_sel	=>  Location: PIN_AB17,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- c_sel	=>  Location: PIN_AA10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- d_sel	=>  Location: PIN_Y14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- e_sel	=>  Location: PIN_V14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- f_sel	=>  Location: PIN_AB22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- g_sel	=>  Location: PIN_AB21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- W	=>  Location: PIN_T12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- X	=>  Location: PIN_T13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Y	=>  Location: PIN_V13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- Z	=>  Location: PIN_U13,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF birthday IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_W : std_logic;
SIGNAL ww_X : std_logic;
SIGNAL ww_Y : std_logic;
SIGNAL ww_Z : std_logic;
SIGNAL ww_g : std_logic;
SIGNAL ww_f : std_logic;
SIGNAL ww_e : std_logic;
SIGNAL ww_d : std_logic;
SIGNAL ww_c : std_logic;
SIGNAL ww_b : std_logic;
SIGNAL ww_a : std_logic;
SIGNAL ww_a_cond : std_logic;
SIGNAL ww_b_cond : std_logic;
SIGNAL ww_c_cond : std_logic;
SIGNAL ww_d_cond : std_logic;
SIGNAL ww_e_cond : std_logic;
SIGNAL ww_f_cond : std_logic;
SIGNAL ww_g_cond : std_logic;
SIGNAL ww_a_sel : std_logic;
SIGNAL ww_b_sel : std_logic;
SIGNAL ww_c_sel : std_logic;
SIGNAL ww_d_sel : std_logic;
SIGNAL ww_e_sel : std_logic;
SIGNAL ww_f_sel : std_logic;
SIGNAL ww_g_sel : std_logic;
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \Y~input_o\ : std_logic;
SIGNAL \Z~input_o\ : std_logic;
SIGNAL \X~input_o\ : std_logic;
SIGNAL \W~input_o\ : std_logic;
SIGNAL \g~0_combout\ : std_logic;
SIGNAL \f~0_combout\ : std_logic;
SIGNAL \e~0_combout\ : std_logic;
SIGNAL \c~0_combout\ : std_logic;
SIGNAL \b~0_combout\ : std_logic;
SIGNAL \a~0_combout\ : std_logic;
SIGNAL \a_cond~0_combout\ : std_logic;
SIGNAL \Mux1~0_combout\ : std_logic;
SIGNAL \Mux2~0_combout\ : std_logic;
SIGNAL \Mux3~0_combout\ : std_logic;
SIGNAL \Mux5~0_combout\ : std_logic;
SIGNAL \g_cond~0_combout\ : std_logic;
SIGNAL \Mux0~0_combout\ : std_logic;
SIGNAL \ALT_INV_g_cond~0_combout\ : std_logic;
SIGNAL \ALT_INV_a_cond~0_combout\ : std_logic;
SIGNAL \ALT_INV_W~input_o\ : std_logic;
SIGNAL \ALT_INV_X~input_o\ : std_logic;
SIGNAL \ALT_INV_Z~input_o\ : std_logic;
SIGNAL \ALT_INV_Y~input_o\ : std_logic;

BEGIN

ww_W <= W;
ww_X <= X;
ww_Y <= Y;
ww_Z <= Z;
g <= ww_g;
f <= ww_f;
e <= ww_e;
d <= ww_d;
c <= ww_c;
b <= ww_b;
a <= ww_a;
a_cond <= ww_a_cond;
b_cond <= ww_b_cond;
c_cond <= ww_c_cond;
d_cond <= ww_d_cond;
e_cond <= ww_e_cond;
f_cond <= ww_f_cond;
g_cond <= ww_g_cond;
a_sel <= ww_a_sel;
b_sel <= ww_b_sel;
c_sel <= ww_c_sel;
d_sel <= ww_d_sel;
e_sel <= ww_e_sel;
f_sel <= ww_f_sel;
g_sel <= ww_g_sel;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\ALT_INV_g_cond~0_combout\ <= NOT \g_cond~0_combout\;
\ALT_INV_a_cond~0_combout\ <= NOT \a_cond~0_combout\;
\ALT_INV_W~input_o\ <= NOT \W~input_o\;
\ALT_INV_X~input_o\ <= NOT \X~input_o\;
\ALT_INV_Z~input_o\ <= NOT \Z~input_o\;
\ALT_INV_Y~input_o\ <= NOT \Y~input_o\;

-- Location: IOOBUF_X46_Y0_N36
\g~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \g~0_combout\,
	devoe => ww_devoe,
	o => ww_g);

-- Location: IOOBUF_X50_Y0_N53
\f~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \f~0_combout\,
	devoe => ww_devoe,
	o => ww_f);

-- Location: IOOBUF_X48_Y0_N93
\e~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \e~0_combout\,
	devoe => ww_devoe,
	o => ww_e);

-- Location: IOOBUF_X50_Y0_N36
\d~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \e~0_combout\,
	devoe => ww_devoe,
	o => ww_d);

-- Location: IOOBUF_X48_Y0_N76
\c~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \c~0_combout\,
	devoe => ww_devoe,
	o => ww_c);

-- Location: IOOBUF_X51_Y0_N36
\b~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \b~0_combout\,
	devoe => ww_devoe,
	o => ww_b);

-- Location: IOOBUF_X52_Y0_N53
\a~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \a~0_combout\,
	devoe => ww_devoe,
	o => ww_a);

-- Location: IOOBUF_X44_Y0_N36
\a_cond~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \ALT_INV_a_cond~0_combout\,
	devoe => ww_devoe,
	o => ww_a_cond);

-- Location: IOOBUF_X40_Y0_N93
\b_cond~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux1~0_combout\,
	devoe => ww_devoe,
	o => ww_b_cond);

-- Location: IOOBUF_X44_Y0_N53
\c_cond~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux2~0_combout\,
	devoe => ww_devoe,
	o => ww_c_cond);

-- Location: IOOBUF_X43_Y0_N36
\d_cond~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux3~0_combout\,
	devoe => ww_devoe,
	o => ww_d_cond);

-- Location: IOOBUF_X38_Y0_N36
\e_cond~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux3~0_combout\,
	devoe => ww_devoe,
	o => ww_e_cond);

-- Location: IOOBUF_X43_Y0_N53
\f_cond~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux5~0_combout\,
	devoe => ww_devoe,
	o => ww_f_cond);

-- Location: IOOBUF_X51_Y0_N53
\g_cond~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \ALT_INV_g_cond~0_combout\,
	devoe => ww_devoe,
	o => ww_g_cond);

-- Location: IOOBUF_X48_Y0_N42
\a_sel~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux0~0_combout\,
	devoe => ww_devoe,
	o => ww_a_sel);

-- Location: IOOBUF_X38_Y0_N53
\b_sel~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux1~0_combout\,
	devoe => ww_devoe,
	o => ww_b_sel);

-- Location: IOOBUF_X22_Y0_N53
\c_sel~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux2~0_combout\,
	devoe => ww_devoe,
	o => ww_c_sel);

-- Location: IOOBUF_X36_Y0_N19
\d_sel~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux3~0_combout\,
	devoe => ww_devoe,
	o => ww_d_sel);

-- Location: IOOBUF_X38_Y0_N19
\e_sel~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux3~0_combout\,
	devoe => ww_devoe,
	o => ww_e_sel);

-- Location: IOOBUF_X46_Y0_N53
\f_sel~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \Mux5~0_combout\,
	devoe => ww_devoe,
	o => ww_f_sel);

-- Location: IOOBUF_X40_Y0_N76
\g_sel~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \ALT_INV_g_cond~0_combout\,
	devoe => ww_devoe,
	o => ww_g_sel);

-- Location: IOIBUF_X33_Y0_N58
\Y~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_Y,
	o => \Y~input_o\);

-- Location: IOIBUF_X33_Y0_N41
\Z~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_Z,
	o => \Z~input_o\);

-- Location: IOIBUF_X34_Y0_N1
\X~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_X,
	o => \X~input_o\);

-- Location: IOIBUF_X34_Y0_N18
\W~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_W,
	o => \W~input_o\);

-- Location: LABCELL_X44_Y1_N0
\g~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \g~0_combout\ = ( \X~input_o\ & ( \W~input_o\ ) ) # ( !\X~input_o\ & ( \W~input_o\ & ( (!\Z~input_o\) # (\Y~input_o\) ) ) ) # ( \X~input_o\ & ( !\W~input_o\ & ( (\Y~input_o\ & \Z~input_o\) ) ) ) # ( !\X~input_o\ & ( !\W~input_o\ & ( !\Y~input_o\ $ 
-- (\Z~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1100001111000011000000110000001111110011111100111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \ALT_INV_Y~input_o\,
	datac => \ALT_INV_Z~input_o\,
	datae => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \g~0_combout\);

-- Location: LABCELL_X44_Y1_N39
\f~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \f~0_combout\ = ( \X~input_o\ & ( \W~input_o\ ) ) # ( !\X~input_o\ & ( \W~input_o\ & ( \Y~input_o\ ) ) ) # ( \X~input_o\ & ( !\W~input_o\ & ( !\Z~input_o\ $ (!\Y~input_o\) ) ) ) # ( !\X~input_o\ & ( !\W~input_o\ & ( \Y~input_o\ ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000111100001111010110100101101000001111000011111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datac => \ALT_INV_Y~input_o\,
	datae => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \f~0_combout\);

-- Location: LABCELL_X44_Y1_N42
\e~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \e~0_combout\ = ( \X~input_o\ & ( \W~input_o\ ) ) # ( !\X~input_o\ & ( \W~input_o\ & ( \Y~input_o\ ) ) ) # ( \X~input_o\ & ( !\W~input_o\ & ( (!\Y~input_o\ & \Z~input_o\) ) ) ) # ( !\X~input_o\ & ( !\W~input_o\ & ( (\Z~input_o\) # (\Y~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011111100111111000011000000110000110011001100111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \ALT_INV_Y~input_o\,
	datac => \ALT_INV_Z~input_o\,
	datae => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \e~0_combout\);

-- Location: LABCELL_X44_Y1_N51
\c~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \c~0_combout\ = ( \X~input_o\ & ( \W~input_o\ ) ) # ( !\X~input_o\ & ( \W~input_o\ & ( \Y~input_o\ ) ) ) # ( \X~input_o\ & ( !\W~input_o\ & ( !\Z~input_o\ $ (!\Y~input_o\) ) ) ) # ( !\X~input_o\ & ( !\W~input_o\ & ( (!\Z~input_o\ & \Y~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000101000001010010110100101101000001111000011111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datac => \ALT_INV_Y~input_o\,
	datae => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \c~0_combout\);

-- Location: LABCELL_X44_Y1_N54
\b~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \b~0_combout\ = ( \X~input_o\ & ( \W~input_o\ ) ) # ( !\X~input_o\ & ( \W~input_o\ & ( (\Z~input_o\) # (\Y~input_o\) ) ) ) # ( \X~input_o\ & ( !\W~input_o\ & ( (!\Y~input_o\ & \Z~input_o\) ) ) ) # ( !\X~input_o\ & ( !\W~input_o\ & ( (\Y~input_o\ & 
-- !\Z~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011000000110000000011000000110000111111001111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \ALT_INV_Y~input_o\,
	datac => \ALT_INV_Z~input_o\,
	datae => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \b~0_combout\);

-- Location: LABCELL_X44_Y1_N33
\a~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \a~0_combout\ = ( \X~input_o\ & ( \W~input_o\ ) ) # ( !\X~input_o\ & ( \W~input_o\ & ( \Y~input_o\ ) ) ) # ( \X~input_o\ & ( !\W~input_o\ & ( (\Z~input_o\ & !\Y~input_o\) ) ) ) # ( !\X~input_o\ & ( !\W~input_o\ & ( \Y~input_o\ ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000111100001111010100000101000000001111000011111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datac => \ALT_INV_Y~input_o\,
	datae => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \a~0_combout\);

-- Location: LABCELL_X44_Y1_N27
\a_cond~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \a_cond~0_combout\ = ( \W~input_o\ & ( (!\Y~input_o\ & !\X~input_o\) ) ) # ( !\W~input_o\ & ( (!\Y~input_o\ & ((!\Z~input_o\) # (!\X~input_o\))) # (\Y~input_o\ & ((\X~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1100101111001011110010111100101111000000110000001100000011000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datab => \ALT_INV_Y~input_o\,
	datac => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \a_cond~0_combout\);

-- Location: LABCELL_X44_Y1_N12
\Mux1~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \Mux1~0_combout\ = ( \X~input_o\ & ( \W~input_o\ ) ) # ( !\X~input_o\ & ( \W~input_o\ & ( (\Z~input_o\) # (\Y~input_o\) ) ) ) # ( \X~input_o\ & ( !\W~input_o\ & ( (!\Y~input_o\ & \Z~input_o\) ) ) ) # ( !\X~input_o\ & ( !\W~input_o\ & ( (\Y~input_o\ & 
-- !\Z~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011000000110000000011000000110000111111001111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \ALT_INV_Y~input_o\,
	datac => \ALT_INV_Z~input_o\,
	datae => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \Mux1~0_combout\);

-- Location: LABCELL_X44_Y1_N18
\Mux2~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \Mux2~0_combout\ = ( \W~input_o\ & ( (\X~input_o\) # (\Y~input_o\) ) ) # ( !\W~input_o\ & ( (!\Z~input_o\ & (\Y~input_o\)) # (\Z~input_o\ & (!\Y~input_o\ & \X~input_o\)) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0010001001100110001000100110011000110011111111110011001111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datab => \ALT_INV_Y~input_o\,
	datad => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \Mux2~0_combout\);

-- Location: LABCELL_X44_Y1_N21
\Mux3~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \Mux3~0_combout\ = ( \W~input_o\ & ( (\X~input_o\) # (\Y~input_o\) ) ) # ( !\W~input_o\ & ( (!\Y~input_o\ & (\Z~input_o\)) # (\Y~input_o\ & ((!\X~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0101111101010000010111110101000000001111111111110000111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datac => \ALT_INV_Y~input_o\,
	datad => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \Mux3~0_combout\);

-- Location: LABCELL_X44_Y1_N24
\Mux5~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \Mux5~0_combout\ = ( \W~input_o\ & ( (\X~input_o\) # (\Y~input_o\) ) ) # ( !\W~input_o\ & ( !\Y~input_o\ $ (((!\Z~input_o\) # (!\X~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011001101100110001100110110011000110011111111110011001111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datab => \ALT_INV_Y~input_o\,
	datad => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \Mux5~0_combout\);

-- Location: LABCELL_X44_Y1_N6
\g_cond~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \g_cond~0_combout\ = ( \W~input_o\ & ( (\Z~input_o\ & (!\Y~input_o\ & !\X~input_o\)) ) ) # ( !\W~input_o\ & ( (!\Z~input_o\ & ((\X~input_o\) # (\Y~input_o\))) # (\Z~input_o\ & (!\Y~input_o\)) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0110011011101110011001101110111001000100000000000100010000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datab => \ALT_INV_Y~input_o\,
	datad => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \g_cond~0_combout\);

-- Location: LABCELL_X44_Y1_N9
\Mux0~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \Mux0~0_combout\ = ( \W~input_o\ & ( (\X~input_o\) # (\Y~input_o\) ) ) # ( !\W~input_o\ & ( (!\Y~input_o\ & (\Z~input_o\ & \X~input_o\)) # (\Y~input_o\ & ((!\X~input_o\))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000111101010000000011110101000000001111111111110000111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_Z~input_o\,
	datac => \ALT_INV_Y~input_o\,
	datad => \ALT_INV_X~input_o\,
	dataf => \ALT_INV_W~input_o\,
	combout => \Mux0~0_combout\);

-- Location: LABCELL_X1_Y3_N3
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


