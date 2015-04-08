//b17.c
//Kevin Hilt
//CSC456
//April 8, 2015
//Purpose:  
//
//Compile:
//          With makefile:
//              make
//
//          Without makefile:
//              gcc -g -Wall-o b17 b17.c
//
//Run:      ./b17 <prog.obj>
//
//              where <prog.obj> is the simulated object file

#include "header.h"

extern int MEMORY[MEMORY_SIZE];

//Author:   Kevin Hilt
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
    if(argc != 2)
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

