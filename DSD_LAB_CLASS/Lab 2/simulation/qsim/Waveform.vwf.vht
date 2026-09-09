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

-- *****************************************************************************
-- This file contains a Vhdl test bench with test vectors .The test vectors     
-- are exported from a vector file in the Quartus Waveform Editor and apply to  
-- the top level entity of the current Quartus project .The user can use this   
-- testbench to simulate his design using a third-party simulation tool .       
-- *****************************************************************************
-- Generated on "09/15/2025 19:45:45"
                                                             
-- Vhdl Test Bench(with test vectors) for design  :          birthday
-- 
-- Simulation tool : 3rd Party
-- 

LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;                                

ENTITY birthday_vhd_vec_tst IS
END birthday_vhd_vec_tst;
ARCHITECTURE birthday_arch OF birthday_vhd_vec_tst IS
-- constants                                                 
-- signals                                                   
SIGNAL a : STD_LOGIC;
SIGNAL a_cond : STD_LOGIC;
SIGNAL a_sel : STD_LOGIC;
SIGNAL b : STD_LOGIC;
SIGNAL b_cond : STD_LOGIC;
SIGNAL b_sel : STD_LOGIC;
SIGNAL c : STD_LOGIC;
SIGNAL c_cond : STD_LOGIC;
SIGNAL c_sel : STD_LOGIC;
SIGNAL d : STD_LOGIC;
SIGNAL d_cond : STD_LOGIC;
SIGNAL d_sel : STD_LOGIC;
SIGNAL e : STD_LOGIC;
SIGNAL e_cond : STD_LOGIC;
SIGNAL e_sel : STD_LOGIC;
SIGNAL f : STD_LOGIC;
SIGNAL f_cond : STD_LOGIC;
SIGNAL f_sel : STD_LOGIC;
SIGNAL g : STD_LOGIC;
SIGNAL g_cond : STD_LOGIC;
SIGNAL g_sel : STD_LOGIC;
SIGNAL W : STD_LOGIC;
SIGNAL X : STD_LOGIC;
SIGNAL Y : STD_LOGIC;
SIGNAL Z : STD_LOGIC;
COMPONENT birthday
	PORT (
	a : OUT STD_LOGIC;
	a_cond : OUT STD_LOGIC;
	a_sel : OUT STD_LOGIC;
	b : OUT STD_LOGIC;
	b_cond : OUT STD_LOGIC;
	b_sel : OUT STD_LOGIC;
	c : OUT STD_LOGIC;
	c_cond : OUT STD_LOGIC;
	c_sel : OUT STD_LOGIC;
	d : OUT STD_LOGIC;
	d_cond : OUT STD_LOGIC;
	d_sel : OUT STD_LOGIC;
	e : OUT STD_LOGIC;
	e_cond : OUT STD_LOGIC;
	e_sel : OUT STD_LOGIC;
	f : OUT STD_LOGIC;
	f_cond : OUT STD_LOGIC;
	f_sel : OUT STD_LOGIC;
	g : OUT STD_LOGIC;
	g_cond : OUT STD_LOGIC;
	g_sel : OUT STD_LOGIC;
	W : IN STD_LOGIC;
	X : IN STD_LOGIC;
	Y : IN STD_LOGIC;
	Z : IN STD_LOGIC
	);
END COMPONENT;
BEGIN
	i1 : birthday
	PORT MAP (
-- list connections between master ports and signals
	a => a,
	a_cond => a_cond,
	a_sel => a_sel,
	b => b,
	b_cond => b_cond,
	b_sel => b_sel,
	c => c,
	c_cond => c_cond,
	c_sel => c_sel,
	d => d,
	d_cond => d_cond,
	d_sel => d_sel,
	e => e,
	e_cond => e_cond,
	e_sel => e_sel,
	f => f,
	f_cond => f_cond,
	f_sel => f_sel,
	g => g,
	g_cond => g_cond,
	g_sel => g_sel,
	W => W,
	X => X,
	Y => Y,
	Z => Z
	);

-- W
t_prcs_W: PROCESS
BEGIN
	W <= '0';
	WAIT FOR 80000 ps;
	W <= '1';
WAIT;
END PROCESS t_prcs_W;

-- X
t_prcs_X: PROCESS
BEGIN
	X <= '0';
	WAIT FOR 40000 ps;
	X <= '1';
	WAIT FOR 40000 ps;
	X <= '0';
	WAIT FOR 40000 ps;
	X <= '1';
WAIT;
END PROCESS t_prcs_X;

-- Y
t_prcs_Y: PROCESS
BEGIN
LOOP
	Y <= '0';
	WAIT FOR 10000 ps;
	Y <= '1';
	WAIT FOR 10000 ps;
	IF (NOW >= 160000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_Y;

-- Z
t_prcs_Z: PROCESS
BEGIN
LOOP
	Z <= '0';
	WAIT FOR 5000 ps;
	Z <= '1';
	WAIT FOR 5000 ps;
	IF (NOW >= 160000 ps) THEN WAIT; END IF;
END LOOP;
END PROCESS t_prcs_Z;
END birthday_arch;
