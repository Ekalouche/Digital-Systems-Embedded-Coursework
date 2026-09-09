LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY Coverter IS
    PORT (
        in_num   : IN  STD_LOGIC_VECTOR(7 downto 0);
        Abs_num  : OUT STD_LOGIC_VECTOR(7 downto 0)
    );
END Coverter;

ARCHITECTURE LogicFunction OF Coverter IS
    SIGNAL in_signed     : SIGNED(7 downto 0);
    SIGNAL inverted_bits : SIGNED(7 downto 0);
    SIGNAL twos_comp     : SIGNED(7 downto 0);
    SIGNAL abs_val       : SIGNED(7 downto 0);
BEGIN

    -- Convert input to signed format
    in_signed <= SIGNED(in_num);

    PROCESS(in_signed)
    BEGIN
        IF in_signed(7) = '1' THEN
            inverted_bits <= NOT in_signed;     -- Invert bits
            twos_comp     <= inverted_bits + 1; -- Add 1
            abs_val       <= twos_comp;         -- Absolute value
        ELSE
            abs_val       <= in_signed;         -- Already positive
        END IF;

        Abs_num <= STD_LOGIC_VECTOR(abs_val);   -- Output as binary encoding of decimal value
    END PROCESS;

END LogicFunction;

