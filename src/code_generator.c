// CS3500 Project - Code Generator
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "write.h"

char *parse_file(FILE*fp){
    char *parsed;                            //Hold parsed characters
    char *chars;                             //Input buffer Holds characters for getline()
    size_t len = 0;                          //Holds the size of the input buffer,
    char *str  = malloc(sizeof(char) * 400); //Buffer with limited to 400 char.
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
            else{                                                   //else the operand isn't supported
                fprintf(stderr, "Unsupported operand: %s \n", s);
                exit(-1);                                           //exit the program.
            }
        }                                    //else if it isn't an operand then it is a number
        else{parsed = strsep(&chars, ",");}
        strcat(str, parsed);                 //concat the number or operand to buffer 'str'.
    }
    strcat(str,"\0");       //at the end we add null character.
    fclose(fp);             //close the file
    return str;             //return the new string.
}

int main(int argc, char**argv) {
    //Error detection
    FILE *fp = NULL;
    fp = fopen("output/i2p.txt","r");                          //Try to open file
    if (fp == NULL){                                    //If the file pointer is null
        fprintf(stderr, "File %s does not exist.\n");   //Then the file doesn't exist
        return 1;
    }
    //End of error detection
    char *str = parse_file(fp);                     //parse the file
    write_file("output/code.txt", str);             //write to new file the parsed data
    return 0;
}
