LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY Final_Calculator IS
    PORT (
        A, B   : IN  STD_LOGIC_VECTOR(3 DOWNTO 0);
        OP     : IN  STD_LOGIC_VECTOR(1 DOWNTO 0);
        HEX3   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- Sign
        HEX2   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- Hundreds
        HEX1   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- Tens
        HEX0   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)   -- Ones
    );
END Final_Calculator;

ARCHITECTURE Structure OF Final_Calculator IS

    -- Internal signal to connect calculator to display
    SIGNAL R_Internal : STD_LOGIC_VECTOR(7 DOWNTO 0):= "00000000";

    -- Component declarations
    COMPONENT signed_Calculator 
        PORT (
            A, B : IN  STD_LOGIC_VECTOR(3 DOWNTO 0);
            OP   : IN  STD_LOGIC_VECTOR(1 DOWNTO 0);
            R    : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
        );
    END COMPONENT;

    COMPONENT CalculatorDisplay
        PORT (
            in_num : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
            HEX3   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            HEX2   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            HEX1   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            HEX0   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
        );
    END COMPONENT;

BEGIN

    -- Math logic
    U1: signed_Calculator
        PORT MAP (
            A => A,
            B => B,
            OP => OP,
            R => R_Internal
        );

    -- Display logic
    U2: CalculatorDisplay
        PORT MAP (
            in_num => R_Internal,
            HEX3   => HEX3,
            HEX2   => HEX2,
            HEX1   => HEX1,
            HEX0   => HEX0
        );


END Structure;