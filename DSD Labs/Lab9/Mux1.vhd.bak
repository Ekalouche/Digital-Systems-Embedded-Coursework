LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY Mux1 IS
    PORT (
        S          : IN  STD_LOGIC;
        Max_value  : OUT STD_LOGIC_VECTOR(23 downto 0)
    );
END Mux1;

ARCHITECTURE LOGICFUNCTION OF Mux1 IS

    CONSTANT VAL_100ms : STD_LOGIC_VECTOR(23 downto 0) := x"4c4b3f";  -- 100ms value
    CONSTANT VAL_100ns : STD_LOGIC_VECTOR(23 downto 0) := x"000004";  -- 100ns value

BEGIN
    PROCESS(S)
    BEGIN
        IF S = '1' THEN
            Max_value <= VAL_100ms;
        ELSE
            Max_value <= VAL_100ns;
        END IF;
    END PROCESS;
END LOGICFUNCTION;