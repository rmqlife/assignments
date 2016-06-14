----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:17:34 11/10/2012 
-- Design Name: 
-- Module Name:    sign_extend816 - Behavioral 
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

entity extend is
    Port ( clk : in  STD_LOGIC;
           en : in  STD_LOGIC;
           data8 : in  STD_LOGIC_VECTOR (7 downto 0);
           data16 : out  STD_LOGIC_VECTOR (15 downto 0));
end sign_extend816;

architecture Behavioral of sign_extend816 is

begin


end Behavioral;

