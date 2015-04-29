#include "b17.h"

void get_address_mode(int IR, int &ABUS, int &MAR)
{
	// get bits 2-5 of instruction
	// immediate
	if( ((IR >> 2 ) & 15) == 1)
	{
		ABUS = 1;
	}
	// Direct
	else
	{
		ABUS = ((IR >> 2 ) & 15);
	}
	// set MAR equal to value for instruction
	MAR = ((IR >> 12 ) & 4095);

	return;
}

void get_instruction(int IR, string &instruction)
{
	// set up array for instruction set
	string in_set[16][4] = { "HALT", "LD", "ADD", "J",
							 "NOP", "ST", "SUB", "JZ",
							 "?", "EM", "CLR","JN",
							 "?", "?", "COM", "JP",
							 "?", "?", "AND", "?",
							 "?", "?", "OR", "?",
							 "?", "?", "XOR", "?",
							 "?", "?", "?", "?",
							 "?", "LDX", "ADDX", "?",
							 "?", "STX", "SUBX", "?",
							 "?", "EMX", "CLRX", "?",
							 "?", "?", "?", "?",
							 "?", "?", "?", "?",
							 "?", "?", "?", "?",
							 "?", "?", "?", "?",
							 "?", "?", "?", "?"};
	int value = ((IR >> 6 ) & 15); // bits 6-9 for row
	int val2 = ((IR >> 10 ) & 3); // bits 10 and 11 for column

	// convert hex values to ints for array index
	hex_to_int(to_string(value), value); 
	hex_to_int(to_string(val2), val2);
	instruction = in_set[value][val2];

	return;

}


void hex_to_int(string hex_string, int& stored_int)
{ 
	stringstream value;
	value << hex << hex_string;
	value >> stored_int;
}

void read_memory(int memory[],  char* filename)
{
	ifstream file;

	// open and error check input file input file
	file.open(filename);
	if(!file)
	{
		cout << "Error opening object file.";
		exit(-1);
	}

	string line, end;
	int temp, temp2, temp3;

	file >> line; // read memory address
	hex_to_int(line, temp); // convert to int and store
	file >> temp2; // number of instructions on line

	// for each read in instruction and stroe it in the correct memory location
	for(int i = 0; i < temp2; i++)
	{
		file >> line;
		hex_to_int(line, temp3);
		memory[temp] = temp3;
		temp++;
	}

	file >> end; // read halt instruction
	getline(file, line); // skip first line

	file >> line;
	// continue untill you reach halt instruction
	while(line != end)
	{
		hex_to_int(line, temp);
		file >> temp2;

		// for each instruction read in and stroe at memory location
		for(int i = 0; i < temp2; i++)
		{
			file >> line;
			hex_to_int(line, temp3);
			memory[temp] = temp3;
			temp++;
		}

		file >> line; // read last line of file 
					// so next open starts at start of input file 
	}

	file.close();
}

void match_instruction(int memory[], int &MAR, int &AC, int &DBUS,
					   int &ABUS, int &IR, int &IC,
					   ofstream &output, string instruction)
{
		// if statement to determine what to do for each instruction
		
		if(instruction == "ADD")
		{
			if(ABUS == 0) //Direct
			{
				AC = AC + memory[MAR];
			}
			else if(ABUS == 1) //Indirect
			{
				AC = AC + MAR;
			}
		}
		if(instruction == "SUB") 
		{
			if(ABUS == 0) //Direct
			{
				AC = AC - memory[MAR];

			}
			else if(ABUS == 1) //Indirect
			{
				AC = AC - MAR;
			}
		}
		if(instruction == "LD") 
		{
			// for immediate loads load MAR directly into AC
			if(ABUS == 1)
			{
				AC = MAR;
			}
			// for direct load memory at index MAR
			else if(ABUS == 0) //Direct
			{
				AC = memory[MAR];
			}
		}
		if(instruction == "ST") 
		{
			// for direct store, store AC directly into memory at index MAR 
			if(ABUS == 0) //Direct
			{
				memory[MAR] = AC;
			}
			else //Illegal
			{
				address_error("illegal", output);
			}
		}
		if(instruction == "EM") 
		{
			if(ABUS == 0) //Direct swap AC and memory at MAR
			{
				DBUS = AC;
				AC = memory[MAR];
				memory[MAR] = DBUS;
			}
			else
			{
				address_error("illegal", output);
			}
		}
		if(instruction == "AND") 
		{
			// for immediate AND use MAR and AC
			if(ABUS == 1)
			{
				AC = MAR & AC; ///// ask karlson
			}
			else if(ABUS == 0) // for direct use memory at index MAR and AC
			{
				AC = memory[MAR] & AC;
			}
	
		}
		if(instruction == "OR") 
		{
			// for immediate OR use MAR and AC
			if(ABUS == 1)
			{
				AC = MAR | AC; ///// ask karlson
			}
			else if(ABUS == 0) // for direct use memory at index MAR and AC
			{
				AC = memory[MAR] | AC;
			}
			
		}
		if(instruction == "XOR") 
		{
			// for immediate XOR use MAR and AC
			if(ABUS == 1)
			{
				AC = MAR ^ AC; ///// ask karlson
			}
			else if(ABUS == 0) // for direct use memory at index MAR and AC
			{
				AC = memory[MAR] ^ AC;
			}
			
		}

		//Different jumps
		if(((instruction == "J") || //Always jump
		   (instruction == "JZ") || //Jump if accumulator is 0
		   (instruction == "JN") || //Jump if the accumulator is negative
		   (instruction == "JP"))) //Jump if the accumulator is positive
		{
			if(ABUS == 0) //Direct
			{
				if(((instruction == "J") || //Always jump
					(instruction == "JZ" && AC == 0) || //Jump if accumulator is 0
					(instruction == "JN" && AC < 0) || //Jump if the accumulator is negative
					(instruction == "JP" && AC > 0))) //Jump if the accumulator is positive
				{
					IR = memory[MAR];
					IC = MAR;
				}
			}

			// if immediate jump set ABUS to random not used number
			// for later formating calls
			if(ABUS == 1)
			{
				ABUS = 8;
			}
			
		}
		//Clear the accumulator
		if(instruction == "CLR")
		{
			AC = 0;            
		}
		//Complement the accumulator
		if(instruction == "COM")
		{
			AC = ~AC;
		}

}

void address_error(string mode, ofstream &output)
{
	output <<  "Machine Halted - " << mode << " addressing mode.\n";
	return;
}

