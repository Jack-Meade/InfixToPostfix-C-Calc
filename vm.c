// CS3500 Project - VM
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char**argv) {
    FILE *fp;
    char *line;
    char *instruction;
    double operands[100];
    ssize_t op = -1;
    size_t len = 0;
    ssize_t read;
    fp = fopen("code.txt", "r");

    if (fp == NULL) { exit(1); }

    while ((read = getline(&line, &len, fp)) != EOF) {
        if (read != 4) {
            instruction = strsep(&line, " ");

            instruction = strsep(&line, " ");
            instruction[strcspn(instruction, "\n")] = 0;

            operands[++op] = strtof(instruction, NULL);
        } else {
            if      (strcmp(line, "EXP\n") == 0) { operands[op-1] = pow(operands[op-1], operands[op]); op--; }
            else if (strcmp(line, "ADD\n") == 0) { operands[op-1] =     operands[op-1] + operands[op]; op--; }
            else if (strcmp(line, "SUB\n") == 0) { operands[op-1] =     operands[op-1] - operands[op]; op--; }
            else if (strcmp(line, "MUL\n") == 0) { operands[op-1] =     operands[op-1] * operands[op]; op--; }
            else if (strcmp(line, "DIV\n") == 0) { operands[op-1] =     operands[op-1] / operands[op]; op--; }
        }
    }
    printf("%4.2f\n", operands[op]);

    free(line);
    fclose(fp);
    return 0;
}
