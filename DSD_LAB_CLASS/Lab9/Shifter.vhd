LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY Shifter IS
    PORT (
        clk      : IN  std_logic;
        reset_n  : IN  std_logic;
		  enable   : IN  std_logic;
        Hex0     : OUT std_logic_vector(6 DOWNTO 0);
        Hex1     : OUT std_logic_vector(6 DOWNTO 0);
        Hex2     : OUT std_logic_vector(6 DOWNTO 0);
        Hex3     : OUT std_logic_vector(6 DOWNTO 0);
        Hex4     : OUT std_logic_vector(6 DOWNTO 0);
        Hex5     : OUT std_logic_vector(6 DOWNTO 0)
    );
END Shifter;

ARCHITECTURE logic_function OF Shifter IS

    TYPE rom_type IS ARRAY(0 TO 23) OF std_logic_vector(6 DownTO 0);
    CONSTANT message : rom_type := (
        "1111001", -- I
        "1000110", -- C
        "0000110", -- E
        "1111111", -- space
        "1000110", -- C
        "1000000", -- O
        "1000111", -- L
        "0100001", -- D
        "1111111", -- space
        "0010010", -- S
        "1000000", -- O
        "0100001", -- D
        "0001000", -- A
        "1111111", -- space
        "0010010", -- S
        "1000000", -- O
        "1000111", -- L
        "0100001", -- D
        "1111111", -- space
        "0001001", -- H
        "0000110", -- E
        "0101111", -- R
        "0000110",  -- E
		  "1111111" -- space
    );
	
	Signal Shift_Register : rom_type;

BEGIN

    PROCESS(clk, reset_n)
    BEGIN
        IF reset_n = '0' THEN
            Shift_Register <= message;
			elsif rising_edge(clk) then
				IF enable = '1' THEN
            Shift_Register(0 to 22) <= Shift_Register(1 to 23);
				Shift_Register(23) <= Shift_Register(0);
            END IF;
			END IF;
    END PROCESS;
	 
    Hex0 <= Shift_Register(5);
    Hex1 <=	Shift_Register(4);
    Hex2 <= Shift_Register(3);
    Hex3 <=	Shift_Register(2);
    Hex4 <= Shift_Register(1);
    Hex5 <= Shift_Register(0);

END logic_function;