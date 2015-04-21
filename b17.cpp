#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

void get_address_mode(int IC, int &address_mode);
void get_instruction(int IC, string &instruction);
void hex_to_int(string hex_string, int& stored_int);
void read_memory(int memory[],  char* filename); 

int main(int argc, char* argv[])
{
	int MAR;
	int IC;
	int X0 = 0;
	int	X1 = 0;
	int X2 = 0;
	int X3 = 0;
	int ABUS;
	int MDR;
	int AC = 0;
	int ALU;
	int IR;
	int DBUS;
	int memory[4096];

	int instruction_number;
	string instruction;
	ifstream file;
	ofstream output;

	read_memory(memory, argv[1]);

	file.open(argv[1]);
	if(!file)
	{
		cout << "Error opening object file.";
		exit(-1);
	}
	output.open("output.txt");
	if(!output)
	{
		cout << "Error opening output file.";
		exit(-1);
	}

	getline(file, instruction);
	file >> hex >> IC >> instruction_number;

	for(int i = 0; i < instruction_number; i++)
	{
		file >> hex >> IR;

		get_instruction(IR, instruction);
		get_address_mode(IR, MAR);


		output << hex << setw( 3 ) << setfill( '0' ) << IC << ": " << setw(6) 
			<< setfill('0') << IR << " " << dec << instruction << " ";
	
	
		if(MAR == 1)
		{
			output << "IMM";
		}
		else
			output << hex << MAR;
	
			output << hex << " AC[" << setw( 6 )
				<< setfill( '0' ) << AC << "] X0[" << setw( 3 ) << setfill( '0' )
				<< X0 << "] X1[" << setw( 3 ) << setfill( '0' ) << X1 << "] X2[" 
				<< setw( 3 ) << setfill( '0' ) << X2 << "] X3[" << setw( 3 )
				<< setfill( '0' ) << X3 << "]" << endl;

		/*if(instruction == "HALT")
		{
			output <<  "Machine Halted - HALT instruction executed";
		}
		else if(instruction == "?")
		{
			output <<  "Machine Halted - undefined opcode";
		}
		else if(instruction == "LDX" || "ADDX" || "STX" || "SUBX" || "EMX" || "CLRX")
		{
			output <<  "Machine Halted - unimplemented opcode";
		}*/
	
		// need to add halt messages for address mode errors

	}
	file.close();
	output.close();
}

void get_address_mode(int IR, int &MAR)
{
	cout << IR << ' ';
	if( ((IR >> 2 ) & 15) == 1)
	{
		MAR = 1;

	}
	else
	{
		MAR = ((IR >> 12 ) & 4095);
		cout << hex << "address " << MAR;
	}

	return;
}

void get_instruction(int IR, string &instruction)
{
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
	int value = ((IR >> 6 ) & 15);
	int val2 = ((IR >> 10 ) & 15);

	hex_to_int(to_string(value), value);
	hex_to_int(to_string(val2), val2);

	instruction = in_set[value][val2];

	cout << "value " << value << " Val2 " << val2 <<" in " << instruction << endl;

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

	file.open(filename);
	if(!file)
	{
		cout << "Error opening object file.";
		exit(-1);
	}

	string line, end;
	int temp, temp2, temp3;

	file >> line;
	hex_to_int(line, temp);
	file >> temp2;

	cout << temp2 << endl;

	for(int i = 0; i < temp2; i++)
	{
		file >> line;
		hex_to_int(line, temp3);
		memory[temp] = temp3;
		temp++;
	}

	file >> end;
	cout << "end " << end << endl;
	getline(file, line);

	file >> line;
	while(line != end)
	{
		hex_to_int(line, temp);
		file >> temp2;

		for(int i = 0; i < temp2; i++)
		{
			file >> line;
			hex_to_int(line, temp3);
			memory[temp] = temp3;
			temp++;
		}

		file >> line;
		cout << "line " << line << endl;
	}

	file.close();
}
