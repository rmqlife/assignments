----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    20:17:03 11/10/2012 
-- Design Name: 
-- Module Name:    controller - Behavioral 
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

entity controller is
    Port ( instruct : in  STD_LOGIC_VECTOR (15 downto 0);
				pc_in : in STD_LOGIC_VECTOR (15 downto 0);
				
           alu_op : out  STD_LOGIC_VECTOR (2 downto 0);
           write_reg : out  STD_LOGIC;--to
           read_mem : out  STD_LOGIC;
           write_mem : out  STD_LOGIC;
           goto_type : out  STD_LOGIC_VECTOR(2 downto 0);
			   
			  --b 010
			  alu_imm : out STD_LOGIC; --ready
			  writeback_not_from_mem : out STD_LOGIC;
           reg_read1 : out  STD_LOGIC_VECTOR (3 downto 0);--to
           reg_read2 : out  STD_LOGIC_VECTOR (3 downto 0);--to
           reg_write : out  STD_LOGIC_VECTOR (3 downto 0);--to
           imm : out  STD_LOGIC_VECTOR (15 downto 0)); --ready
end controller;

architecture Behavioral of controller is
begin
	process(instruct)
	begin
		case (instruct(15 downto 11)) is
			--signed(7 downto 0)
			when "01001" | "00000" | "01100"           | "00100" | "00101" | "10010" | "01010" | "11010"=> 
				-- addiu  |  addsp3 |addsp bteqz btnez  |  beqz   |  bnez   | lw_sp   | slti    | sw_sp 
				imm<=instruct(7)&instruct(7)&instruct(7)&instruct(7)&instruct(7)
					&instruct(7)&instruct(7)&instruct(7)
					&instruct(7 downto 0);
			--zero(7 downto 0)
			when "01101" => --li
				imm<="00000000"&instruct(7 downto 0);
			--signed(3 downto 0)
			when "01000"=> --addiu3
				imm<=instruct(3)&instruct(3)&instruct(3)&instruct(3)&instruct(3)
					&instruct(3)&instruct(3)&instruct(3)&instruct(3)&instruct(3)
					&instruct(3)&instruct(3)
					&instruct(3 downto 0);
			--signed(10 downto 0)
			when "00010"=> --b
				imm<=instruct(10)&instruct(10)&instruct(10)&instruct(10)&instruct(10)
					&instruct(10 downto 0);
			--signed(4 downto 0)
			when "10011" | "11011" => --lw | sw
				imm<=instruct(4)&instruct(4)&instruct(4)&instruct(4)&instruct(4)
					&instruct(4)&instruct(4)&instruct(4)&instruct(4)&instruct(4)
					&instruct(4)
					&instruct(4 downto 0);
			--zero(4 downto 2)
			when "00110" => --sll | sra 000->1000 others
				imm<="0000000000000"&
						--(not instruct(4) and not instruct(3) and not instruct(2)) 
						instruct(4 downto 2);
			when "11101" =>
				--mfpc
				imm<=pc_in;
			when others =>
				imm<=(others => '0');
		end case;
	end process;
	
	
	process(instruct)
	begin
		case instruct(15 downto 11) is
		--rx<=rx
		when "01001" =>
			-- addiu
			goto_type<="000";
			alu_op<="000";			
			alu_imm<='1';
			write_reg<='1';
			reg_read1<='0'&instruct(10 downto 8);
			reg_write<='0'&instruct(10 downto 8);
		--ry<=rx
		when "01000" =>
			-- addiu3
			goto_type<="000";			
			alu_op<="000";
			alu_imm<='1';
			write_reg<='1';
			reg_read1<='0'&instruct(10 downto 8);
			reg_write<='0'&instruct(7 downto 5);
		--rx<=sp+imm
		when "00000"=>
			-- addsp3
			goto_type<="000";			
			alu_op<="000";
			alu_imm<='1';
			write_reg<='1';
			reg_read1<="1001";--sp
			reg_write<='0'&instruct(10 downto 8);
		--sp<=sp
		when "01100"=>
			case (instruct(10 downto 8)) is
				when "011"=>
					--addsp
					goto_type<="000";
					alu_op<="000";
					alu_imm<='1';
					write_reg<='1';
					reg_read1<="1001";--sp
					reg_write<="1001";--sp
				when "000"=>
				--bteqz
					goto_type<="010"; --bteqz
					alu_op<="001"; --minus
					write_reg<='0';
					reg_read1<="1010";--t
					reg_read2<="1000";--zero
					alu_imm<='0';--t-0
				when "001"=>
					--btnez
					goto_type<="011"; --btnez
					alu_op<="001"; --minus
					write_reg<='0';
					reg_read1<="1010";--t
					reg_read2<="1000";--zero
					alu_imm<='0';--t-0
				when "100"=>
					--mtsp sp<=rx+0
					goto_type<="000";
					alu_imm<='0';
					alu_op<="000";
					write_reg<='1';
					reg_write<="1001";--sp
					reg_read1<='0'&instruct(10 downto 8);
					reg_read2<="1000";--zero
				when others=>
			end case;
		--rz<=rx+ry
		when "11100"=>
			case (instruct(1 downto 0)) is
				when "11"=>
				--subu
				goto_type<="000";
				alu_op<="001";--minus
				alu_imm<='0';
				write_reg<='1';
				reg_read1<='0'&instruct(10 downto 8);
				reg_read2<='0'&instruct(7 downto 5);
				reg_write<='0'&instruct(4 downto 2);
				when "01"=>
				--addu
				goto_type<="000";
				alu_op<="000";
				alu_imm<='0';			
				write_reg<='1';
				reg_read1<='0'&instruct(10 downto 8);
				reg_read2<='0'&instruct(7 downto 5);
				reg_write<='0'&instruct(4 downto 2);
				when others=>
			end case;
		--goto | addto immediate
		when "00010"=>
			--b : 0 + imm
			goto_type<="001";	--b		
			write_reg<='0';
		when "00100"=>
			--beqz rx==0 jump
			goto_type<="010";	--beqz		
			alu_op<="001"; --minus
			write_reg<='0';
			reg_read1<='0'&instruct(10 downto 8);
			reg_read2<="1000";--zero
			alu_imm<='0';--rx-0
		when "00101"=>
			--bnez rx!=0  jump
			goto_type<="011"; --bnez
			alu_op<="001"; --minus
			write_reg<='0';
			reg_read1<='0'&instruct(10 downto 8);
			reg_read2<="1000";--zero
			alu_imm<='0';--rx-0
		when "11101"=>
			case (instruct(4 downto 0)) is
				when "01010"=>
				--cmp rx ry
				goto_type<="000";
				alu_op<="110"; --A=B?0:1;
				write_reg<='1';
				reg_read1<='0'&instruct(10 downto 8);
				reg_read2<='0'&instruct(7 downto 5);
				reg_write<="1010";--t
				alu_imm<='0';
				
				when "00000"=>
				---warning
				case (instruct(7 downto 5)) is
					when "000"=>
						--jr rx
						goto_type<="100";--jr
						alu_op<="000";--rx+0
						write_reg<='0';
						reg_read1<='0'&instruct(10 downto 8);
						reg_read2<="1000";
						alu_imm<='0';
					when "010"=>
						--mfpc rx<=pc(imm)
						goto_type<="000";
						alu_op<="000";--imm+0
						write_reg<='1';
						reg_write<='0'&instruct(10 downto 8);
						alu_imm<='1';
						reg_read1<="1000";--zero
					when others=>
				end case;
				
				when "01100"=>
					--and rx<=rx and ry
					goto_type<="000";			
					alu_op<="010";--and
					alu_imm<='0';
					write_reg<='1';
					reg_read1<='0'&instruct(10 downto 8);
					reg_read2<='0'&instruct(7 downto 5);
					reg_write<='0'&instruct(10 downto 8);
				when "01101"=>
					--or rx<=rx or ry
					goto_type<="000";			
					alu_op<="011";--or
					alu_imm<='0';				
					write_reg<='1';
					reg_read1<='0'&instruct(10 downto 8);
					reg_read2<='0'&instruct(7 downto 5);
					reg_write<='0'&instruct(10 downto 8);
				when "01011"=>
					--neg rx=0-ry
					goto_type<="000";
					alu_op<="001";--minus
					alu_imm<='0';
					reg_read1<="1000";--zero
					reg_read2<='0'&instruct(7 downto 5);
					reg_write<='0'&instruct(10 downto 8);
					write_reg<='1';
				when others =>
			end case;
		when "01101"=>
			--li rx<=zero(imm)
			goto_type<="000";
			write_reg<='1';
			reg_write<='0'&instruct(10 downto 8);
			reg_read1<="1000";--rz
			alu_imm<='1';
			alu_op<="000";-- rx<=imm+0
		
		when "10011"=>
			--lw ry<=mem(rx+imm)
			goto_type<="000";
			reg_read1<='0'&instruct(10 downto 8);
			alu_imm<='1';
			alu_op<="000";
			reg_write<='0'&instruct(7 downto 5);
			write_reg<='1';
		when "10010"=>
			--lw_sp rx<=mem(sp+imm)
			goto_type<="000";
			reg_write<='0'&instruct(10 downto 8);
			alu_imm<='1';
			alu_op<="000";
			reg_read1<="1001";--sp
			write_reg<='1';	
		when "11110"=>
			case (instruct(7 downto 0)) is
				when "00000000"=>
					--mfih rx<=ih+0
					goto_type<="000";
					reg_write<='0'&instruct(10 downto 8);

					alu_imm<='0';
					alu_op<="000";
					reg_read1<="1011";--ih
					reg_read2<="1000";--zero
					write_reg<='1';
				when "00000001"=>
					--mtih ih<=rx+0
					goto_type<="000";
					reg_write<="1011";--ih
					alu_imm<='0';
					alu_op<="000";
					reg_read1<='0'&instruct(10 downto 8);
					reg_read2<="1000";--zero
					write_reg<='1';
				when others=>
			end case;
			--end 11110
		when "01111" =>
			--move rx<=ry+0
			goto_type<="000";
			reg_write<='0'&instruct(10 downto 8);
			write_reg<='1';
			reg_read1<='0'&instruct(7 downto 5);
			alu_op<="000";
			reg_read2<="1000";--zero
			alu_imm<='0';
		when "00001"=>
			--nop
			goto_type<="000";
			alu_imm<='0';
			alu_op<="000";
			write_reg<='0';
			reg_read1<="1000";
			reg_read2<="1001";
		when "11011"=>
			--sw mem(rx+imm)<=ry
			goto_type<="000";
			alu_op<="000";
			alu_imm<='1';
			reg_read1<='0'&instruct(10 downto 8);
			reg_read2<='0'&instruct(7 downto 5);
			write_reg<='0';
		when "11010"=>
			--sw_sp mem(sp+imm)<=rx
			goto_type<="000";
			alu_op<="000";
			alu_imm<='1';
			reg_read2<='0'&instruct(10 downto 8);
			reg_read1<="1001";
			write_reg<='0';
		when "00110"=>
			case (instruct(1 downto 0)) is
				when "00"=>
				--sll rx<=ry<<imm
				goto_type<="000";
				alu_op<="100";--a<<b
				reg_read1<='0'&instruct(7 downto 5);
				reg_write<='0'&instruct(10 downto 8);
				write_reg<='1';
				alu_imm<='1';
				
				when "11"=>
				--sra rx<=ry>>imm(arith)
				goto_type<="000";
				alu_op<="101";--a>>b
				reg_read1<='0'&instruct(7 downto 5);
				reg_write<='0'&instruct(10 downto 8);
				write_reg<='1';
				alu_imm<='1';
				when others=>
			end case;
			--end 00110
		when "01010"=>
			--slti t<=rx<imm
			goto_type<="000";
			alu_op<="111";--A<B?1:0;
			write_reg<='1';
			reg_write<="1010";--t
			reg_read1<='0'&instruct(10 downto 8);
			alu_imm<='1';
		when others =>
		end case;
	end process;
	
	process (instruct) --mem
	begin
	case(instruct(15 downto 11)) is
		when "10011" | "10010"=>
		--lw | lw_sp rx<=mem
		writeback_not_from_mem<='0'; --writeback from mem
		read_mem<='1';
		write_mem<='0';
		when "11011" | "11010" =>
		--sw | sw_sp mem<=rx
		writeback_not_from_mem<='1'; --writeback from alu
		read_mem<='0';
		write_mem<='1';
		when others=>
		writeback_not_from_mem<='1'; --writeback from alu
		read_mem<='0';
		write_mem<='0';
	end case;
	end process;
end Behavioral;

