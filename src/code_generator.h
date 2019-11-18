// CS3500 Project - Code Generator
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "write.h"

#define BUFFER_SIZE             400
#define INPUT_FILE              "../output/i2p.txt"
#define OUTPUT_FILE             "../output/code.txt"

#define ERROR_INVALID_OPERAND   "Error: Invalid Operand\n"
#define ERROR_NULL_INPUT        "Error: Input file doesn't exist\n"
/*
parse_file
---DESCRIPTION---
Reads in file & creates formatted version as it goes through, line by line.

---INPUT---
*fp: pointer to file

---OUTPUT---
Formatted string:
-25
7.25
3
MUL
2
EXP
SUB
320
...
*/
char *parse_file(FILE*fp){
    char *parsed;                            //Hold parsed characters
    char *chars;                             //Input buffer Holds characters for getline()
    size_t len = 0;                          //Holds the size of the input buffer,
    char *str  = malloc(sizeof(char) * BUFFER_SIZE); //Buffer with limited to 400 char.
    while (getline(&chars, &len, fp) != EOF){                       //While not at the end of the file
        char *s = strsep(&chars, ",");                              //Split the string ',' to get first part
        if (strcmp(s, "o") == 0){                                   //If it's 'o' then do operators
            s = strsep(&chars, ",");                                //Split again to get second part of string
            if      (strcmp(s, "^\n") == 0)  {parsed = "EXP\n";}    //Compare and transform operands
            else if (strcmp(s, "%\n") == 0)  {parsed = "MOD\n";}
            else if (strcmp(s, "*\n") == 0)  {parsed = "MUL\n";}
            else if (strcmp(s, "/\n") == 0)  {parsed = "DIV\n";}
            else if (strcmp(s, "+\n") == 0)  {parsed = "ADD\n";}
            else if (strcmp(s, "-\n") == 0)  {parsed = "SUB\n";}
            else{
                printf("%s\n",ERROR_INVALID_OPERAND);                //else the operand isn't supported
            }
        }
        else{parsed = strsep(&chars, ",");}         //else if it isn't an operand then it is a number
        strcat(str, parsed);                        //concat the number or operand to buffer 'str'.
    }
    strcat(str,"\0");               //at the end we add null character.
    fclose(fp);                     //close the file
    return str;                     //return the new string.
}
