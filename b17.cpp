#include "b17.h"

int main(int argc, char* argv[])
{
	int MAR;
	int IC;
	int X0 = 0;
	int	X1 = 0;
	int X2 = 0;
	int X3 = 0;
	int ABUS = 0;
	int MDR = 0;
	int AC = 0;
	int ALU = 0;
	int IR = 0;
	int DBUS = 0;
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
		get_address_mode(IR, ABUS, MAR);
		match_instruction(memory, MAR, AC, DBUS, ABUS, IR, IC, output, instruction);

		output << hex << setw( 3 ) << setfill( '0' ) << IC << ": " << setw(6) 
			<< setfill('0') << IR << " " << dec << instruction << " ";
		IC++;
	
		if(ABUS == 1)
		{
			output << "IMM";
		}
		else if(ABUS != 0) //Illegal addressing mode
		{
			output << "???";
		}
		else
			output << hex << MAR;
	
			output << hex << " AC[" << setw( 6 )
				<< setfill( '0' ) << AC << "] X0[" << setw( 3 ) << setfill( '0' )
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
	}
	
	get_instruction(IR, instruction);
	get_address_mode(IR, ABUS, MAR);
	match_instruction(memory, MAR, AC, DBUS, ABUS, IR, IC, output, instruction);

	output << hex << setw( 3 ) << setfill( '0' ) << IC << ": " << setw(6) 
		<< setfill('0') << IR << " " << dec << instruction << " ";
	IC++;

	if(ABUS == 1)
	{
		output << "IMM";
	}
	else if(ABUS != 0) //Illegal addressing mode
	{
		output << "???";
	}
	else
		output << hex << MAR;

		output << hex << " AC[" << setw( 6 )
			<< setfill( '0' ) << AC << "] X0[" << setw( 3 ) << setfill( '0' )
			<< X0 << "] X1[" << setw( 3 ) << setfill( '0' ) << X1 << "] X2[" 
			<< setw( 3 ) << setfill( '0' ) << X2 << "] X3[" << setw( 3 )
			<< setfill( '0' ) << X3 << "]" << endl;
	if(instruction == "HALT")
	{
		output <<  "Machine Halted - HALT instruction executed";
		exit(-1);
	}
	else if(instruction == "?")
	{
		output <<  "Machine Halted - undefined opcode";
		exit(-1);
	}
	else if(instruction == "LDX" || "ADDX" || "STX" || "SUBX" || "EMX" || "CLRX")
	{
		output <<  "Machine Halted - unimplemented opcode";
		exit(-1);
	}
	// need to add halt messages for address mode errors
	file.close();
	output.close();
}



