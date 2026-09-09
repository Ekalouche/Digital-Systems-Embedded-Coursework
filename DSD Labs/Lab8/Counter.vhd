LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;


ENTITY counter IS
    PORT (
        set_n   : IN  STD_LOGIC;
        time_n    : IN  STD_LOGIC_VECTOR(9 downto 0);
        enable  : IN  STD_LOGIC;
        reset_n : IN  STD_LOGIC;
        clk     : IN  STD_LOGIC;
        count   : OUT STD_LOGIC_VECTOR(9 downto 0)
    );
END counter;

ARCHITECTURE LOGICFUNCTION OF counter IS

    CONSTANT Nines : UNSIGNED(9 downto 0) := "1111100111";
    SIGNAL inside_count : UNSIGNED(9 downto 0);

BEGIN
    PROCESS(clk,reset_n) is
    BEGIN 
       IF (reset_n = '0') THEN
                inside_count <= (others => '0');
		  elsIF rising_edge(clk) THEN
            IF (set_n = '0') THEN
                inside_count <= unsigned(time_n);
            ELSIF (enable = '1') THEN
                IF (inside_count >= Nines) THEN
                    inside_count <= (others => '0');
                ELSE
                    inside_count <= inside_count + "0000000001";
                END IF;
            END IF;
        END IF;
   END PROCESS;

    count <= std_logic_vector(inside_count);

END LOGICFUNCTION;