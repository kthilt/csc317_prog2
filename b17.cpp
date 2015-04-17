/*/////////////////////////////////////////////////////////////////////////////
b17.c
Kevin Hilt
CSC456
April 8, 2015
Purpose:  

Compile:
          With makefile:
              make

          Without makefile:
              gcc -g -Wall-o b17 b17.c

Run:      ./b17 <prog.obj>

              where <prog.obj> is the simulated object file
*//////////////////////////////////////////////////////////////////////////////

#include "header.h"

//Declare b17 architecture variables
int MEMORY[MEMORY_SIZE]; //Main memory of the b17 --> 4096 24-bit numbers
int MAR; //Memory address register --> 12 bits
int* REGISTERS[4]; //Fout registers --> 12 bits each
int A_BUS; //Address bus --> 12 bits
int MDR; //Memory data register --> 24 bits
int ACC; //Accumulator --> 24 bits
int ALU; //Arithmetic-logic unit --> 24 bits
int IR; //Instruction register --> 24 bits
int D_BUS; //Data bus --> 24 bits

//Author: Kevin Hilt
//Called when the program is run with an invalid number of command line
//arguments
void usage()
{
    printf("Invalid number of command line arguments.\n"
           "Run the program using\n\n\t./b17 <prog.obj>\n\n"
           "where <prog.obj> is the simulated object file.\n");
           
}

//Author: Kevin Hilt
//Processes command line arguments and ...
int main(int argc, char** argv)
{
    if(argc != 2) //Invalid number of command line arguments
    {
        usage();
        return -1;
    }
    
    //Open the object file at argv[1]
    FILE* object_file;
    object_file = fopen(argv[1], "r");
    if(!object_file)
    {
        printf("Could not open %s\n", argv[1]);
        return -2;
    }
    
    //For now, just testing communication between the files and showing
    //both are modifying and same MEMORY[] 
    printf("b17:\t\t\t Setting MEMORY[0] to 1\n");
    MEMORY[0] = 1;
    printf("b17:\t\t\t MEMORY[0] == %d\n", MEMORY[0]);
    
    parse_object_file(object_file);
    
    printf("b17:\t\t\t MEMORY[0] == %d\n", MEMORY[0]);
    
    fclose(object_file);

    return 0;
}

