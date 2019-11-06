// CS3500 Project - Code Generator
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char *parse_file(FILE*fp){
    char *parsed;                   //Hold parsed characters
    char *chars;                    //Input buffer Holds characters for getline()
    size_t len = 0;                 //Holds the size of the input buffer,
    char *str  = malloc(400);       //Buffer with size of the file.
    while (getline(&chars, &len, fp) != EOF){
        char *s = strsep(&chars, ",");
        if (strcmp(s, "O") == 0){
            s = strsep(&chars, ",");
            if (strcmp(s, "^\n") == 0)       {parsed = "EXP\n";}
            else if (strcmp(s, "*\n") == 0)  {parsed = "MUL\n";}
            else if (strcmp(s, "/\n") == 0)  {parsed = "DIV\n";}
            else if (strcmp(s, "+\n") == 0)  {parsed = "ADD\n";}
            else if (strcmp(s, "-\n") == 0)  {parsed = "SUB\n";}
            else{
                fprintf(stderr, "Unsupported operand: %s \n", s);
                exit(-1);
            }
        }
        else{parsed = strsep(&chars, ",");}
        strcat(str, parsed);
    }
    strcat(str,"\0");
    fclose(fp);
    return str;
}
int write_file(FILE*fp, char *c){

    fprintf(fp, "%s", c);
    return 0;
}

int main(int argc, char**argv) {
    //Error detection
    if (argc < 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    FILE *fp = NULL;
    fp = fopen(argv[1],"r");
    if (fp == NULL){
        fprintf(stderr, "File %s does not exist.\n", argv[1]);
        return 1;
    }
    char *str = parse_file(fp);
    printf("%s", str);

    FILE *output = fopen("out.txt", "w");
    write_file(output, str);
    return 0;
}
