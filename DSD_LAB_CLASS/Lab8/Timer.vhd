LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY timer IS
    PORT (
		  set_n    : IN  STD_LOGIC;
		  time_n   : IN  STD_LOGIC_VECTOR(9 DOWNTO 0);
        clk      : IN  STD_LOGIC;
        reset_n  : IN  STD_LOGIC;
        S        : IN  STD_LOGIC;
        HEX2     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- Hundreds
        HEX1     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);  -- Tens
        HEX0     : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)   -- Ones
    );
END timer;

ARCHITECTURE LogicFunction OF timer IS

    -- Internal signals to connect modules
    SIGNAL max_value    : STD_LOGIC_VECTOR(23 DOWNTO 0) := (others => '0');
    SIGNAL delay_flag   : STD_LOGIC := '0';
    SIGNAL counter_out  : STD_LOGIC_VECTOR(9 DOWNTO 0) := (others => '0');

    -- Component declarations
    COMPONENT Mux1
        PORT (
            S         : IN  STD_LOGIC;
            Max_value : OUT STD_LOGIC_VECTOR(23 DOWNTO 0)
        );
    END COMPONENT;

    COMPONENT delay_unit
        PORT (
            max_value : IN  STD_LOGIC_VECTOR(23 DOWNTO 0);
            clk       : IN  STD_LOGIC;
            reset_n   : IN  STD_LOGIC;
            flag      : OUT STD_LOGIC
        );
    END COMPONENT;

    COMPONENT counter
        PORT (
            set_n   : IN  STD_LOGIC;
            time_n    : IN  STD_LOGIC_VECTOR(9 DOWNTO 0);
            enable  : IN  STD_LOGIC;
            reset_n : IN  STD_LOGIC;
            clk     : IN  STD_LOGIC;
            count   : OUT STD_LOGIC_VECTOR(9 DOWNTO 0)
        );
    END COMPONENT;

    COMPONENT binary2ssd
        PORT (
            in_num : IN  STD_LOGIC_VECTOR(9 DOWNTO 0);
            HEX2   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            HEX1   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
            HEX0   : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
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

    -- Counter
    U3: counter
        PORT MAP (
            set_n   => set_n,
            time_n    => time_n,
            enable  => delay_flag,
            reset_n => reset_n,
            clk     => clk,
            count   => counter_out
        );

    -- Display
    U4: binary2ssd
        PORT MAP (
            in_num => counter_out(9 DOWNTO 0),  -- Lower 8 bits to SSD
            HEX2   => HEX2,
            HEX1   => HEX1,
            HEX0   => HEX0
        );

END LogicFunction;