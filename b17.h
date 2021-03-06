/*****************************************************************************
 * @file 
 *
 * @brief This file contains the header information for the b17 program
 * (function prototypes and includes)
 *
 * @mainpage b17.cpp
 ****************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

void get_address_mode(int IR, int &ABUS);
void get_instruction(int IR, string &instruction);
void hex_to_int(string hex_string, int& stored_int);
void read_memory(int memory[], int instruction_number, int MAR,  int &MDR, char* filename);
void match_instruction(int memory[], int &MAR, int &AC, int &DBUS, int &ABUS,
					   int &IC, int &IR, ofstream &output, string instruction);
void address_error(string mode, ofstream &output);