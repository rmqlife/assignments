----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:39:30 11/10/2012 
-- Design Name: 
-- Module Name:    data_ram - Behavioral 
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

entity data_ram is
    Port ( address : in  STD_LOGIC_VECTOR (15 downto 0);
           mem_read : in  STD_LOGIC;
           mem_write : in  STD_LOGIC;
           data_write : in  STD_LOGIC_VECTOR (15 downto 0);
           data_read : out  STD_LOGIC_VECTOR (15 downto 0);
			  clk : in  STD_LOGIC;
           en : in  STD_LOGIC);
end data_ram;

architecture Behavioral of data_ram is

begin


end Behavioral;

