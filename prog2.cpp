#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

int get_address_mode(int IC);
void get_instruction(int IC, string &instruction);
void hex_to_int(string hex_string, int& stored_int);

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

	int instruction_number;
	string instruction;
	ifstream file;
	ofstream output;

	file.open(argv[1]);
	if(!file)
	{
		cout << "Error opening object file.";
		exit(-1);
	}

	file >> hex >> MAR >> instruction_number >> IC;
	cout << MAR << ' ' << instruction_number << ' ' << IC << endl;
	
	get_instruction(IC, instruction);
	get_address_mode(IC);

	output.open("output.txt");
	if(!output)
	{
		cout << "Error opening output file.";
		exit(-1);
	}

	output << hex << setw( 3 ) << setfill( '0' ) << MAR << ": " << setw(6) 
		<< setfill('0') << IC << " " << dec << instruction << " " << "address mode" << " AC[" << setw( 6 )
		<< setfill( '0' ) << AC << "] X0[" << setw( 3 ) << setfill( '0' )
		<< X0 << "] X1[" << setw( 3 ) << setfill( '0' ) << X1 << "] X2[" 
		<< setw( 3 ) << setfill( '0' ) << X2 << "] X3[" << setw( 3 )
		<< setfill( '0' ) << X3 << "]";

	if(instruction == "HALT")
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
	}
	
	// need to add halt messages for address mode errors

}

int get_address_mode(int IC)
{
	int address_mode;
	cout << IC << ' ';
	if( ((IC >> 2 ) & 15) == 1)
	{
		address_mode = 1;
		cout << address_mode;

	}
	else
	{
		address_mode = ((IC >> 12 ) & 4095);
		cout << address_mode;
	}

	return IC;
}

void get_instruction(int IC, string &instruction)
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
	int value = ((IC >> 6 ) & 15);
	int val2 = ((IC >> 10 ) & 15);

	instruction = in_set[value][val2];

	return;

}

void hex_to_int(string hex_string, int& stored_int)
{ 
    stringstream value;
    value << hex << hex_string;
    value >> stored_int;
} 