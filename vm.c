// CS3500 Project - VM
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    FILE *fp;
    char *line;
    char *instruction;
    size_t len = 0;
    ssize_t read;
    fp = fopen("code.txt", "r");

    if (fp == NULL) { exit(1); }

    while ((read = getline(&line, &len, fp)) != EOF) {
        if (read != 4) {
            while( (instruction = strsep(&line, " ")) != NULL ) {
                printf("%s\n", instruction);
            }
        } else {
            printf("%s\n", line);
        }
    }

    // TODO: Able to parse instructions
    //       need to operate on operands

    free(line);
    fclose(fp);
    return 0;
}
