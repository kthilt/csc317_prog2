/*************************************************************************//**
 * @file 
 *
 * @brief This file contains the main function for the b17
 *
 * @mainpage b17.cpp
 * 
 * @section course_section Course Information 
 *
 * @authors Marcus Berger, Kevin Hilt, Evan Hammer
 * 
 * @date May 1th, 2015
 * 
 * @par Professor: 
 *         Dr. Karlson 
 * 
 * @par Course: 
 *         CSC 317 - 1:00 pm
 * 
 * @par Location: 
 *         McLaury - 205
 *
 * @section program_section Program Information 
 * 
 * @details The B17 is a 24-bit word-addressable accumulator architecture. 
 * It supports up to 64 instructions, up to four addressing modes, 
 * and 212 (4096) words of memory. Main memory consists of 4,096 words, each 
 * of which is 24 bits wide. Addresses are 12 bits wide, and range from 000 
 * through FFF. Within the word, bits are numbered from right to left, with bit
 * 0 the least significant bit and bit 23 the most significant bit. The memory
 * interface transfers one word of data at a time. Communication with memory 
 * is via two registers, MAR and MDR. Other locations include IC, ABUS, DBUS
 * three registers, AC, ALU and IR. The B17 uses fixed-length instructions. 
 * Instructions have the following format an ADDR a twelve-bit operand address
 * (bits 23-12), a six-bit opcode (bits 11-6), and a six-bit addressing mode 
 * (bits 5-0). The b17 uses those bits to determine the instruction to be
 * executed from the instruction set. The program continues to execute
 * instructions untill a halt instruction is found or a halting error occurs.
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *      compile with C++11 
 * 
 * @par Usage: 
   @verbatim  
   b17 "input file"
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug direct address of two digits do not contain leading zeros in
 * format string
 * 
 *
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   April 21, 2015 Started and wrote general algorithm
   April 23, 2015 Start instruction set
   April 28, 2015 Finsh instruction set, halting, and errors (program complete)
   April 28-30, 2015 Finish Documentation
   @endverbatim
 *
 *****************************************************************************/
#include "b17.h"

int main(int argc, char* argv[])
{
	int MAR; // memory address register
	int IC; // instruction counter
	int X0 = 0; // register 0
	int	X1 = 0; // register 1
	int X2 = 0; // register 2
	int X3 = 0; // register 3
	int ABUS = 0; 
	int MDR = 0; // memory data register
	int AC = 0; // 
	int ALU = 0; // athimetic logic unit
	int IR = 0; // instruction register
	int DBUS = 0; // data bus
	int memory[4096]; // memory array

	int instruction_number; // number of instruction read in
	string instruction; // current instruction
	ifstream file; // input file
	ofstream output; // output file

	read_memory(memory, argv[1]); 

	// open and error check input file
	file.open(argv[1]);
	if(!file)
	{
		cout << "Error opening object file.";
		return -1;
	}
	// open output and error check output file
	output.open("output.txt");
	if(!output)
	{
		cout << "Error opening output file.";
		return -1;
	}

	// use getline to skip first line
	getline(file, instruction);
	// read in number of instructions
	file >> hex >> IC >> instruction_number;

	for(int i = 0; i < instruction_number; i++)
	{
		file >> hex >> IR; // read in instruction

		// decode instruction
		get_instruction(IR, instruction);
		// decode address mode
		get_address_mode(IR, ABUS, MAR);
		//do correct instruction
		match_instruction(memory, MAR, AC, DBUS, ABUS, IR, IC, output, instruction);

		// output the Instruction counter and instruction with padding
		output << hex << setw( 3 ) << setfill( '0' ) << IC << ": " << setw(6) 
			<< setfill('0') << IR << " " << dec << left << setw(4) 
			<< setfill(' ') << instruction << " ";
		IC++;
	
		// check for immediate or illegal address mode
		if(ABUS == 1)
		{
			output << "IMM ";
		}
		else if(ABUS != 0) //Illegal addressing mode
		{
			output << "??? ";
		}
		else if(MAR == 0)
		{
			output << "    ";
		}
		else // print MAR if direct addressing mode
			output << hex << left << setw(4) << setfill(' ') << MAR;
			
			// use bitwise and to match wanted formatting
			AC = AC & 0xffffff;
			// output the rest of the formating AC, X0, X1, X2, X3
			output << hex << " AC[" << setw( 6 )
				<< setfill( '0' ) << right << AC  << "] X0[" << setw( 3 ) << setfill( '0' )
				<< X0 << "] X1[" << setw( 3 ) << setfill( '0' ) << X1 << "] X2[" 
				<< setw( 3 ) << setfill( '0' ) << X2 << "] X3[" << setw( 3 )
				<< setfill( '0' ) << X3 << "]" << endl;
		
		
		if(ABUS == 2 || ABUS == 4 || ABUS == 6) //unimplemented addressing mode
		{
			address_error("unimplemented", output);
		}
		else if(ABUS != 0  && ABUS != 1) //illegal addressing mode
		{
			address_error("illegal", output);
		}
		if(instruction == "HALT") // check for HALT instruction completion
		{
			output <<  "Machine Halted - HALT instruction executed\n";
			return 0;
		}
		// check for undefined opcode
		else if(instruction == "?")
		{
			output <<  "Machine Halted - undefined opcode\n";
			return 0;
		}
		// check for unimplemented opcode
		else if(instruction == "LDX" || instruction ==  "ADDX" || 
				instruction ==  "STX" || instruction ==  "SUBX" || 
				instruction == "EMX" || instruction ==  "CLRX")
		{
			output <<  "Machine Halted - unimplemented opcode\n";
			return 0;
		}
	}

	//decode instruction
	get_instruction(IR, instruction);
	// decode address mode
	get_address_mode(IR, ABUS, MAR);
	// get which instruction to do
	match_instruction(memory, MAR, AC, DBUS, ABUS, IR, IC, output, instruction);

	// output next instruction counter and instruction
	output << hex << setw( 3 ) << setfill( '0' ) << IC << ": " << setw(6) 
		<< setfill('0') << IR << " " << dec << left << setw(4) 
		<< setfill(' ') << instruction << " ";
	IC++;

	// check for immediate address mode
	if(ABUS == 1)
	{
		output << "IMM ";
	}
	else if(ABUS != 0) //Illegal addressing mode
	{
		output << "??? ";
	}
	else if(MAR == 0)
	{
		output << "    ";
	}
	else // output MAR for direct addressing mode
		output << hex << left << setw(4) << setfill(' ') << MAR;

		output << hex << " AC[" << setw( 6 )
			<< setfill( '0' ) << right << AC << "] X0[" << setw( 3 ) << setfill( '0' )
			<< X0 << "] X1[" << setw( 3 ) << setfill( '0' ) << X1 << "] X2[" 
			<< setw( 3 ) << setfill( '0' ) << X2 << "] X3[" << setw( 3 )
			<< setfill( '0' ) << X3 << "]" << endl;
			
	if(instruction == "HALT") // Halt complete
	{
		output <<  "Machine Halted - HALT instruction executed\n";
		return 0;
	}
	else if(instruction == "?") // undefined opcode halt
	{
		output <<  "Machine Halted - undefined opcode\n";
		return 0;
	}
	else if(instruction == "LDX" || "ADDX" || "STX" || "SUBX" || "EMX" || "CLRX")
	{
		output <<  "Machine Halted - unimplemented opcode\n";
		return 0;
	}
	file.close();
	output.close();
	
	return 0;
}

