----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:09:39 11/10/2012 
-- Design Name: 
-- Module Name:    mux3_2 - Behavioral 
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

entity mux3_2 is
    Port ( d0 : in  STD_LOGIC_VECTOR (2 downto 0);
           d1 : in  STD_LOGIC_VECTOR (2 downto 0);
           dout : out  STD_LOGIC_VECTOR (2 downto 0);
           s : in  STD_LOGIC);
end mux3_2;

architecture Behavioral of mux3_2 is

begin


end Behavioral;

