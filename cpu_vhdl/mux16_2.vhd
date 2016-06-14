----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:08:05 11/10/2012 
-- Design Name: 
-- Module Name:    mux16_2 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity mux16_2 is
    Port ( d0 : in  STD_LOGIC_VECTOR (15 downto 0);
           d1 : in  STD_LOGIC_VECTOR (15 downto 0);
           dout : out  STD_LOGIC_VECTOR (15 downto 0);
           s : in  STD_LOGIC);
end mux16_2;

architecture Behavioral of mux16_2 is
begin
process(s)
begin
	case (s) is
		when '1'=>
			dout<=d1;
		when others=>
			dout<=d0;
	end case;
end process;
end Behavioral;

