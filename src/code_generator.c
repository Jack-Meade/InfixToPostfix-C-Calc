// CS3500 Project - Code Generator compiler
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade
// Author: Daniels Bindemans
#include "code_generator.h"

char *parse_file(char *input_file){
    FILE *fp = NULL;                                                //Try to open file if file is null
    if (!(fp = fopen(input_file, "r"))) {return ERROR_NULL_INPUT;}  //Then the file doesn't exist
    char *parsed;                                                   //Hold parsed characters
    char *chars;                                                    //Input buffer Holds characters for getline()
    size_t len = 0;                                                 //Holds the size of the input buffer,
    char *str  = malloc(sizeof(char) * BUFFER_SIZE);                //Buffer with limited to 400 char.
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
            else    {return ERROR_INVALID_OPERAND;}                 //else the operand isn't supported
        }
        else if(strcmp(s,"n") == 0) {parsed = strsep(&chars, ",");} //else if it isn't an operand then it is a number
        else{return ERROR_INVALID_FILE_FORMAT;}
        strcat(str, parsed);                                        //concat the number or operand to buffer 'str'.
    }
    strcat(str,"\0");               //at the end we add null character.
    fclose(fp);                     //close the file
    return str;                     //return the new string.
}
