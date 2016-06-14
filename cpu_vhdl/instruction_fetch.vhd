----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:50:34 11/10/2012 
-- Design Name: 
-- Module Name:    instruction_fetch - Behavioral 
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

entity instruction_fetch is
    Port ( pc_in : in  STD_LOGIC_VECTOR (15 downto 0);
           ins_out : out  STD_LOGIC_VECTOR (15 downto 0);
           clk : in  STD_LOGIC;
           en : in  STD_LOGIC);
end instruction_fetch;

architecture Behavioral of instruction_fetch is

begin


end Behavioral;

