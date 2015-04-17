/*/////////////////////////////////////////////////////////////////////////////
header.h
Kevin Hilt
CSC456
April 8, 2015
Purpose:  
*//////////////////////////////////////////////////////////////////////////////

#include "header.h"

//Author: Kevin Hilt
//Takes the passed string of a hex value and stores it into the passed int
//You can then output the int back as hex using
//      cout << hex << integer_name;
void hex_to_int(string hex_string, int& stored_int)
{ 
    stringstream value;
    value << hex << hex_string;
    value >> stored_int;
} 

//Author: Kevin Hilt
//Takes the passed object file and parses through, filling the specified
//addresses in MEMORY[] with their associated values
void parse_object_file(FILE* object_file)
{
    //This is just testing that global MEMORY[] works for now
    printf("parse_object_file.c:\t MEMORY[0] == %d\n", MEMORY[0]);
    printf("parse_object_file.c:\t Setting MEMORY[0] to 2\n");
    MEMORY[0] = 2;
    printf("parse_object_file.c:\t MEMORY[0] == %d\n", MEMORY[0]);
    
    cout << "\nOriginal hex value to test = 050\n";
    
    hex_to_int("050", MDR);
    
    cout << "integer value of MDR = " << MDR << "\n";
    cout << "hex value of MDR = " << hex << MDR << "\n\n";
}

