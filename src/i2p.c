// CS3500 Project - Infix To Postfix
// Conor Patrick Mc Donald
/*------------------------------DESCRIPTION---------------------------------------
i2p.c takes an input file consisting of infix expressions, converts to postfix format
and then outputs into a file called i2p.txt */

#include "i2p.h"

int main(int argc, char const *argv[]) {
    //opening the file
    char *output;
    FILE *fp = NULL;
    fp = fopen("output/tokens.txt","r");
    if (fp == NULL){
        fprintf(stderr, "File does not exist.\n");
        return 1;
    }
    else{
        output = parse_file(fp);
        if (strcmp(output, ERROR_BAD_INPUT) == 0){

          fprintf(stderr, "%s\n", ERROR_BAD_INPUT); return 1;
          }
        else if(strcmp(output, ERROR_MISMATCHED_BRACKETS) == 0){

          fprintf(stderr, "%s\n", ERROR_MISMATCHED_BRACKETS);return 1;
        }

    }
    // Generate postfix from file
    write_file("output/i2p.txt", parse_file(fp));
}
