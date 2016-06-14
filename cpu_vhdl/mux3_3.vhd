----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:41:35 11/10/2012 
-- Design Name: 
-- Module Name:    mux3_3 - Behavioral 
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

entity mux3_3 is
    Port ( d00 : in  STD_LOGIC_VECTOR (2 downto 0);
           d01 : in  STD_LOGIC_VECTOR (2 downto 0);
           s : in  STD_LOGIC_VECTOR (1 downto 0);
           d10 : in  STD_LOGIC_VECTOR (2 downto 0);
           dout : out  STD_LOGIC_VECTOR (2 downto 0));
end mux3_3;

architecture Behavioral of mux3_3 is

begin


end Behavioral;

