#include "b17.h"

void get_address_mode(int IR, int &ABUS)
{
	cout << IR << ' ';
	if( ((IR >> 2 ) & 15) == 1)
	{
		ABUS = 1;

	}
	else
	{
		ABUS = ((IR >> 12 ) & 4095);
		cout << hex << "address " << ABUS;
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
	int val2 = ((IR >> 10 ) & 3);

	hex_to_int(to_string(value), value);
	cout << value << endl;
	hex_to_int(to_string(val2), val2);
	cout << val2 << endl;
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