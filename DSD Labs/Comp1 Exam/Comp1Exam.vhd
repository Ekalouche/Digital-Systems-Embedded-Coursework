--Elie Kalouche
LIBRARY ieee;
USE ieee.std_logic_1164.all;


ENTITY Comp1Exam IS
	PORT(D,E,F :IN 	STD_LOGIC; -- ALL Input 
					X	 :OUT  STD_LOGIC); --ALL Outputs
		
END Comp1Exam; --Ends Entity

ARCHITECTURE LogicFunction OF Comp1Exam IS -- Begins Architecture
  signal inputs : STD_LOGIC_VECTOR(2 DOWNTO 0); --initializing the Vector inputs
  BEGIN

       inputs <= D & E & F; --Concatenation Of the 3 input Bits 
       X <= '1' WHEN inputs = "000" or inputs = "001" or inputs = "011" or inputs = "111" else '0'; -- Conditional Statement 

  END logicFunction; --End of Architecture 