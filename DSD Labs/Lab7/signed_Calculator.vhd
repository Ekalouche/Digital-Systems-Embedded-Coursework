Library ieee;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

Entity signed_Calculator IS
    Port( A,B : IN STD_LOGIC_VECTOR(3 downto 0);
          OP  : IN STD_LOGIC_VECTOR(1 downto 0);
          R   : OUT STD_LOGIC_VECTOR(7 downto 0));
end signed_Calculator;

Architecture behavior of signed_Calculator IS
    signal a_signed, b_signed : SIGNED(3 downto 0);
    signal op_signed          : SIGNED(1 downto 0);
begin 

	a_signed <= SIGNED(A);
	b_signed <= SIGNED(B);
    
	process(a_signed, b_signed, op) 

    begin
   

        case op is
            when "00" =>
                R <= STD_LOGIC_VECTOR( (a_signed(3) & a_signed(3) & a_signed(3) & a_signed(3) & a_signed) + (b_signed(3) & b_signed(3) & b_signed(3) & b_signed(3) & b_signed));
            when "01" =>
                R <= STD_LOGIC_VECTOR( (a_signed(3) & a_signed(3) & a_signed(3) & a_signed(3) & a_signed) - (b_signed(3) & b_signed(3) & b_signed(3) & b_signed(3) & b_signed));
            when "10" =>
                R <= STD_LOGIC_VECTOR( (a_signed) * (b_signed));
            when "11" =>
                R <= STD_LOGIC_VECTOR( (a_signed(3) & a_signed(3) & a_signed(3) & a_signed(3) & a_signed) / (b_signed));
            when others =>
                R <= (others => '0');
        end case;
    end process;
end behavior;