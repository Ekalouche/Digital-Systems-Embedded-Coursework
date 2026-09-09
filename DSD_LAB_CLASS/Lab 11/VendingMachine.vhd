library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity VendingMachine is
    Port (
        Clk         : in  STD_LOGIC;
        Reset_n     : in  STD_LOGIC;
        Nickel_In   : in  STD_LOGIC;
        Dime_In     : in  STD_LOGIC;
        Quarter_In  : in  STD_LOGIC;
        Dispense    : in  STD_LOGIC;
        Coin_return : in  STD_LOGIC;
        Red_Bull    : out STD_LOGIC;
        Change_back : out STD_LOGIC;
        HEX0        : out STD_LOGIC_VECTOR(6 downto 0);
        HEX1        : out STD_LOGIC_VECTOR(6 downto 0)
    );
end VendingMachine;

architecture Behavioral of VendingMachine is

    type State_Type is (wait1, dime, nickel, quarter, enough, excess, vend, change);
    signal current_state, next_state : State_Type;

    signal money      : unsigned(7 downto 0) := (others => '0');
    signal money_next : unsigned(7 downto 0);

begin

    --------------------------------------------------------------------
    -- State Register
    --------------------------------------------------------------------
    process(Clk, Reset_n)
    begin
        if Reset_n = '0' then
            current_state <= wait1;
            money <= (others => '0');
        elsif rising_edge(Clk) then
            current_state <= next_state;
            money <= money_next;
        end if;
    end process;

    --------------------------------------------------------------------
    -- Next State Logic
    --------------------------------------------------------------------
    process(current_state, Nickel_In, Dime_In, Quarter_In, Dispense, Coin_return, money)
    begin
        next_state <= current_state; -- default
        case current_state is
            when wait1 =>
                if Coin_return = '1' then
                    next_state <= change;
                elsif Quarter_In = '1' and money < to_unsigned(75,8) then
                    next_state <= quarter;
                elsif Dime_In = '1' and money < to_unsigned(75,8) then
                    next_state <= dime;
                elsif Nickel_In = '1' and money < to_unsigned(75,8) then
                    next_state <= nickel;
                elsif (Quarter_In = '1' or Dime_In = '1' or Nickel_In = '1') and money >= to_unsigned(75,8) then
                    next_state <= enough;
                end if;

            when dime =>
                if money + to_unsigned(10,8) >= to_unsigned(75,8) then
                    next_state <= enough;
                else
                    next_state <= wait1;
                end if;

            when nickel =>
                if money + to_unsigned(5,8) >= to_unsigned(75,8) then
                    next_state <= enough;
                else
                    next_state <= wait1;
                end if;

            when quarter =>
                if money + to_unsigned(25,8) >= to_unsigned(75,8) then
                    next_state <= enough;
                else
                    next_state <= wait1;
                end if;

            when enough =>
                if Coin_return = '1' then
                    next_state <= change;
                elsif Dispense = '1' then
                    next_state <= vend;
                elsif (Quarter_In = '1' or Dime_In = '1' or Nickel_In = '1') then
                    next_state <= excess;
                end if;

            when excess =>
                if Dispense = '1' then
                    next_state <= vend;
                elsif (Quarter_In = '1' or Dime_In = '1' or Nickel_In = '1') then
                    next_state <= excess;
                end if;

            when vend =>
                if money > to_unsigned(0,8) then
                    next_state <= change;
                else
                    next_state <= wait1;
                end if;

            when change =>
                if Coin_return = '1' then
                    next_state <= wait1;
                else
                    next_state <= wait1; -- default return
                end if;

            when others =>
                next_state <= wait1;
        end case;
    end process;

    --------------------------------------------------------------------
    -- Money Update Logic
    --------------------------------------------------------------------
    process(current_state, money)
    begin
        case current_state is
            when dime    => money_next <= money + to_unsigned(10,8);
            when nickel  => money_next <= money + to_unsigned(5,8);
            when quarter => money_next <= money + to_unsigned(25,8);
            when vend    => money_next <= money - to_unsigned(75,8);
            when change  => money_next <= (others => '0');
            when others  => money_next <= money;
        end case;
    end process;

    --------------------------------------------------------------------
    -- Red_Bull Output
    --------------------------------------------------------------------
    process(current_state)
    begin
        if current_state = vend then
            Red_Bull <= '1';
        else
            Red_Bull <= '0';
        end if;
    end process;

    --------------------------------------------------------------------
    -- Change_back Output
    --------------------------------------------------------------------
    process(current_state)
    begin
        if current_state = change then
            Change_back <= '1';
        else
            Change_back <= '0';
        end if;
    end process;

    --------------------------------------------------------------------
    -- HEX Display Output (stub)
    --------------------------------------------------------------------
    process(money)
    begin
        HEX0 <= "0000000"; -- blank
        HEX1 <= "0000000"; -- blank
        -- TODO: add segment decoder for money value
    end process;

end Behavioral;