/*/////////////////////////////////////////////////////////////////////////////
header.h
Kevin Hilt
CSC456
April 8, 2015
Purpose:  Libraries, declarations of architecture variables, and prototypes
*//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

#define MEMORY_SIZE 4096

//Required b17 architecture variables
extern int MEMORY[MEMORY_SIZE]; //Main memory of the b17 --> 4096 24-bit numbers
extern int MAR; //Memory address register --> 12 bits
extern int* REGISTERS[4]; //Fout registers --> 12 bits each
extern int A_BUS; //Address bus --> 12 bits
extern int MDR; //Memory data register --> 24 bits
extern int ACC; //Accumulator --> 24 bits
extern int ALU; //Arithmetic-logic unit --> 24 bits
extern int IR; //Instruction register --> 24 bits
extern int D_BUS; //Data bus --> 24 bits

//Additional b17 architecture variables (if needed)
//...
//...

//PROTOTYPES///////////////////////////////////////////////////////////////////
//parse_object_file.c
void parse_object_file(FILE* object_file);

