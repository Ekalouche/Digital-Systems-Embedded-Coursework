LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY birthday IS
PORT(W,X,Y,Z :IN 	STD_LOGIC;
	   g,f,e,d,c,b,a	 :OUT  STD_LOGIC;
		a_cond,b_cond,c_cond,d_cond,e_cond,f_cond,g_cond :OUT STD_LOGIC;
		a_sel,b_sel,c_sel,d_sel,e_sel,f_sel,g_sel :OUT STD_LOGIC);
		
END birthday;

ARCHITECTURE LogicFunction OF birthday IS 
signal inputs : STD_LOGIC_VECTOR(3 DOWNTO 0);
BEGIN

a <= (not W and not X and Y and not Z) or
          (not W and not X and Y and Z) or
          (not W and X and not Y and Z) or
          (W and not X and Y and not Z) or
          (W and not X and Y and Z) or
          (W and X and not Y and not Z) or
          (W and X and not Y and Z) or
          (W and X and Y and not Z) or
          (W and X and Y and Z);

b <= (not W and not X and Y and not Z) or
          (not W and X and not Y and Z) or
          (W and not X and not Y and Z) or
          (W and not X and Y and not Z) or
          (W and not X and Y and Z) or
          (W and X and not Y and not Z) or
          (W and X and not Y and Z) or
          (W and X and Y and not Z) or
          (W and X and Y and Z);

c <= (not W and not X and Y and not Z) or
          (not W and X and not Y and Z) or
          (not W and X and Y and not Z) or
          (W and not X and Y and not Z) or
          (W and not X and Y and Z) or
          (W and X and not Y and not Z) or
          (W and X and not Y and Z) or
          (W and X and Y and not Z) or
          (W and X and Y and Z);

d <= (not W and not X and not Y and Z) or
          (not W and not X and Y and not Z) or
          (not W and not X and Y and Z) or
          (not W and X and not Y and Z) or
          (W and not X and Y and not Z) or
          (W and not X and Y and Z) or
          (W and X and not Y and not Z) or
          (W and X and not Y and Z) or
          (W and X and Y and not Z) or
          (W and X and Y and Z);

e <= (not W and not X and not Y and Z) or
          (not W and not X and Y and not Z) or
          (not W and not X and Y and Z) or
          (not W and X and not Y and Z) or
          (W and not X and Y and not Z) or
          (W and not X and Y and Z) or
          (W and X and not Y and not Z) or
          (W and X and not Y and Z) or
          (W and X and Y and not Z) or
          (W and X and Y and Z);

f <= (not W and not X and Y and not Z) or
          (not W and not X and Y and Z) or
          (not W and X and not Y and Z) or
          (not W and X and Y and not Z) or
          (W and not X and Y and not Z) or
          (W and not X and Y and Z) or
          (W and X and not Y and not Z) or
          (W and X and not Y and Z) or
          (W and X and Y and not Z) or
          (W and X and Y and Z);

g <= (not W and not X and not Y and not Z) or
          (not W and not X and Y and Z) or
          (not W and X and Y and Z) or
          (W and not X and not Y and not Z) or
          (W and not X and Y and Z) or
          (W and not X and Y and not Z) or
          (W and X and not Y and not Z) or
          (W and X and not Y and Z) or
          (W and X and Y and not Z) or
          (W and X and Y and Z);


inputs <= W & X & Y & Z;
a_cond <= '1' WHEN inputs = "0010" or inputs = "0011" or inputs = "0101" or inputs = "1010" or inputs = "1011" or inputs = "1100" or inputs = "1101" or inputs = "1110" or inputs = "1111"  else '0';
B_cond <= '1' WHEN inputs = "0010" or inputs = "0101" or inputs = "1001" or inputs = "1010" or inputs = "1011" or inputs = "1100" or inputs = "1101" or inputs = "1110" or inputs = "1111"  else '0';
c_cond <= '1' WHEN inputs = "0010" or inputs = "0101" or inputs = "0110" or inputs = "1010" or inputs = "1011" or inputs = "1100" or inputs = "1101" or inputs = "1110" or inputs = "1111"  else '0'; 
d_cond <= '1' WHEN inputs = "0001" or inputs = "0010" or inputs = "0011" or inputs = "0101" or inputs = "1010" or inputs = "1011" or inputs = "1100" or inputs = "1101" or inputs = "1110" or inputs = "1111"  else '0';
e_cond <= '1' WHEN inputs = "0001" or inputs = "0010" or inputs = "0011" or inputs = "0101" or inputs = "1010" or inputs = "1011" or inputs = "1100" or inputs = "1101" or inputs = "1110" or inputs = "1111"  else '0';
f_cond <= '1' WHEN inputs = "0010" or inputs = "0011" or inputs = "0101" or inputs = "0110" or inputs = "1010" or inputs = "1011" or inputs = "1100" or inputs = "1101" or inputs = "1110" or inputs = "1111"  else '0';
g_cond <= '1' WHEN inputs = "0000" or inputs = "0011" or inputs = "0111" or inputs = "1000" or inputs = "1010" or inputs = "1011" or inputs = "1100" or inputs = "1101" or inputs = "1110" or inputs = "1111"  else '0';

WITH inputs SELECT
	a_sel <= '1' WHEN "0010" | "0011" | "0101" | "1010" | "1011" | "1100" | "1101" | "1110" | "1111", '0' WHEN OTHERS;
	

WITH inputs SELECT
	b_sel <= '1' WHEN "0010"| "0101" | "1001" | "1010" | "1011" | "1100" | "1101" | "1110" | "1111", '0' WHEN OTHERS;


WITH inputs SELECT
	c_sel <= '1' WHEN "0010" | "0101" | "0110" | "1010" | "1011" | "1100" | "1101" | "1110" | "1111", '0' WHEN OTHERS;

	
WITH inputs SELECT
	d_sel <= '1' WHEN "0001" | "0010" | "0011" | "0101" | "1010" | "1011" | "1100" | "1101" | "1110" | "1111", '0' WHEN OTHERS;



WITH inputs SELECT
	e_sel <= '1' WHEN "0001" | "0010" | "0011" | "0101" | "1010" | "1011" | "1100" | "1101" | "1110" | "1111", '0' WHEN OTHERS;

	

WITH inputs SELECT
	f_sel <= '1' WHEN "0010" | "0011" | "0101" | "0110" | "1010" | "1011" | "1100" | "1101" | "1110" | "1111", '0' WHEN OTHERS;



WITH inputs SELECT
	g_sel <= '1' WHEN "0000" | "0011" | "0111" | "1000" | "1010" | "1011" | "1100" | "1101" | "1110" | "1111", '0' WHEN OTHERS;

END logicFunction;