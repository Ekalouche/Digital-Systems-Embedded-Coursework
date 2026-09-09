LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY Shifting_display IS
    PORT (
        clk      : IN  STD_LOGIC;
        reset_n  : IN  STD_LOGIC;
        S        : IN  STD_LOGIC;
        HEX0     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
        HEX1     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
        HEX2     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
        HEX3     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
        HEX4     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
        HEX5     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
    );
END Shifting_display;

ARCHITECTURE LogicFunction OF Shifting_display IS

    -- Internal signals
    SIGNAL max_value   : STD_LOGIC_VECTOR(27 DOWNTO 0) := (others => '0');
    SIGNAL delay_flag  : STD_LOGIC := '0';

    -- Component declarations
    COMPONENT Mux1
        PORT (
            S         : IN  STD_LOGIC;
            Max_value : OUT STD_LOGIC_VECTOR(27 DOWNTO 0)
        );
    END COMPONENT;

    COMPONENT delay_unit
        PORT (
            max_value : IN  STD_LOGIC_VECTOR(27 DOWNTO 0);
            clk       : IN  STD_LOGIC;
            reset_n   : IN  STD_LOGIC;
            flag      : OUT STD_LOGIC
        );
    END COMPONENT;

    COMPONENT Shifter
        PORT (
            clk     : IN  STD_LOGIC;
            reset_n : IN  STD_LOGIC;
				enable   : IN  std_logic;
            Hex0    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            Hex1    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            Hex2    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            Hex3    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            Hex4    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            Hex5    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
        );
    END COMPONENT;

BEGIN

    -- Mux logic
    U1: Mux1
        PORT MAP (
            S         => S,
            Max_value => max_value
        );

    -- Delay unit
    U2: delay_unit
        PORT MAP (
            max_value => max_value,
            clk       => clk,
            reset_n   => reset_n,
            flag      => delay_flag
        );

    -- Shifter display
    U3: Shifter
        PORT MAP (
				enable  => delay_flag,
            clk     => clk,
            reset_n => reset_n,
            Hex0    => HEX0,
            Hex1    => HEX1,
            Hex2    => HEX2,
            Hex3    => HEX3,
            Hex4    => HEX4,
            Hex5    => HEX5
        );

END LogicFunction;