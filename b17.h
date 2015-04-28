#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

void get_address_mode(int IR, int &ABUS);
void get_instruction(int IC, string &instruction);
void hex_to_int(string hex_string, int& stored_int);
void read_memory(int memory[],  char* filename);
void match_instruction(int memory[], int &MAR, int &AC, int DBUS, int ABUS, 
					   string instruction);