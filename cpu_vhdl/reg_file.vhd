----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:29:28 11/10/2012 
-- Design Name: 
-- Module Name:    reg_file - Behavioral 
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

entity reg_file is
    Port ( reg_read1 : in  STD_LOGIC_VECTOR (2 downto 0);
           reg_read2 : in  STD_LOGIC_VECTOR (2 downto 0);
           reg_write : in  STD_LOGIC_VECTOR (2 downto 0);
           data_write : in  STD_LOGIC_VECTOR (15 downto 0);
           clk : in  STD_LOGIC;
           en : in  STD_LOGIC;
			  write_reg : in STD_LOGIC;
           data_read1 : out  STD_LOGIC_VECTOR (15 downto 0);
           data_read2 : out  STD_LOGIC_VECTOR (15 downto 0));
end reg_file;

architecture Behavioral of reg_file is

begin


end Behavioral;

