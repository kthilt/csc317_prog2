//parse_object_file.c
//Kevin Hilt
//CSC456
//April 8, 2015
//Purpose:  
//

#include "header.h"

extern int MEMORY[MEMORY_SIZE];

//Author: Kevin Hilt
//Takes the passed object file and parses through, filling the specified
//addresses in MEMORY[] with their associated values
void parse_object_file(FILE* object_file)
{
    printf("parse_object_file.c:\t MEMORY[0] == %d\n", MEMORY[0]);
    printf("parse_object_file.c:\t Setting MEMORY[0] to 2\n");
    MEMORY[0] = 2;
    printf("parse_object_file.c:\t MEMORY[0] == %d\n", MEMORY[0]);
}

