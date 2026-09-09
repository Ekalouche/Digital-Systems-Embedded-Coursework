LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ENTITY delay_unit IS
    PORT (
        max_value : IN  STD_LOGIC_VECTOR(27 downto 0);
        clk       : IN  STD_LOGIC;
        reset_n   : IN  STD_LOGIC;
        flag      : OUT STD_LOGIC
    );
END delay_unit;

ARCHITECTURE LOGICFUNCTION OF delay_unit IS

    SIGNAL int_count : UNSIGNED(27 downto 0);

BEGIN
    -- Counter process
    PROCESS(clk, reset_n)
    BEGIN
        IF (reset_n = '0') THEN
            int_count <= (others => '0');
        ELSIF (clk'event AND clk = '1') THEN
            IF (int_count = unsigned(max_value)) THEN
                int_count <= (others => '0');
            ELSE
                int_count <= int_count + 1;
            END IF;
        END IF;
    END PROCESS;

    -- Flag output process
    PROCESS(clk, reset_n)
    BEGIN
        IF (reset_n = '0') THEN
            flag <= '0';
        ELSIF (clk'event AND clk = '1') THEN
            IF (int_count = unsigned(max_value)) THEN
                flag <= '1';
            ELSE
                flag <= '0';
            END IF;
        END IF;
    END PROCESS;

END LOGICFUNCTION;