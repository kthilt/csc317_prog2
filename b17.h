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

void get_address_mode();
void get_instruction();
void hex_to_int(string hex_string, int& stored_int);
void read_memory(char* filename);
void match_instruction(ofstream &output, string instruction);
void address_error(string mode, ofstream &output);

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
