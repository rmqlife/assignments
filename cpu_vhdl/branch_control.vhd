----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    20:00:17 11/10/2012 
-- Design Name: 
-- Module Name:    branch_control - Behavioral 
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
use ieee.std_logic_unsigned.all;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity branch_control is
    Port ( 
			  current_pc : in STD_LOGIC_VECTOR (15 downto 0);
			  goto_type : in  STD_LOGIC_VECTOR (2 downto 0);
           next_pc : out  STD_LOGIC_VECTOR (15 downto 0);
           alu_out : in  STD_LOGIC_VECTOR (15 downto 0);
			  imm_out : in  STD_LOGIC_VECTOR (15 downto 0);
           alu_eqz : in  STD_LOGIC);
end branch_control;
 
architecture Behavioral of branch_control is
begin
process(goto_type)
begin
	case (goto_type) is 
		when "000"=>
			--goto next
			next_pc<=current_pc+'1';
		when "001"=>
			--b
			next_pc<=current_pc+imm_out;
		when "010"=>
			--bteqz beqz 
			if  alu_eqz ='1' then
				next_pc<=current_pc+imm_out;
			else 
				next_pc<=current_pc+'1';
			end if;
		when "011"=>
			--bnez btnez
			if  alu_eqz ='0' then
				next_pc<=current_pc+imm_out;
			else 
				next_pc<=current_pc+'1';
			end if;
		when "100"=>
			--jr
			next_pc<=alu_out;
		when others=>
			next_pc<=current_pc+'1';
	end case;
end process;

end Behavioral;

