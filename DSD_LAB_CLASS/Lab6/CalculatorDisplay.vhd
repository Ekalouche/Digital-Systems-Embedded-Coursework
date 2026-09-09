LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY CalculatorDisplay IS
    PORT (
        in_num : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
        HEX3   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- Sign (from Sign_mux)
        HEX2   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- Hundreds (from Displayer)
        HEX1   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- Tens (from Displayer)
        HEX0   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)   -- Ones (from Displayer)
    );
END CalculatorDisplay;

ARCHITECTURE Structure OF CalculatorDisplay IS

    -- Component declarations
    COMPONENT Sign_mux
        PORT (
            in_num : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
            HEX3   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
        );
    END COMPONENT;

    COMPONENT Coverter
        PORT (
            in_num  : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
            Abs_num : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
        );
    END COMPONENT;

    COMPONENT Displayer
        PORT (
            Abs_num : IN  STD_LOGIC_VECTOR(7 DOWNTO 0);
            HEX2    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            HEX1    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
	    HEX0    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
        );
    END COMPONENT;

    -- Internal signal to carry absolute value
    SIGNAL abs_val : STD_LOGIC_VECTOR(7 DOWNTO 0);

BEGIN

    -- Sign detection
    U1: Sign_mux
        PORT MAP (
            in_num => in_num,
            HEX3   => HEX3
        );

    -- Absolute value conversion
    U2: Coverter
        PORT MAP (
            in_num  => in_num,
            Abs_num => abs_val
        );

    -- Decimal display
    U3: Displayer
        PORT MAP (
            Abs_num => abs_val,
            HEX2    => HEX2,
            HEX1    => HEX1,
            HEX0    => HEX0  -- Renamed to HEX0 to avoid conflict with Sign_mux
        );

END Structure;