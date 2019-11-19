// CS3500 Project - VM Header
// Author: Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACK_SIZE 200
#define INPUT_FILE "output/code.txt"

/*
---DESCRIPTION---
Executes VM using code from Code Generator.

---INPUT---
*filename:      string of file were code is located

---OUTPUT---
Result of calculation from instructions
*/
float execute(char *filename) {
    FILE *fp;
    char *instruction;                                      // Buffer which holds current instruction
    float operands[STACK_SIZE];                             // Operand stack
    int op = -1;                                            // Pointer to current operand in stack
    size_t len = 0;                                         // Pointer to size of buffer (needed for getline())
    fp = fopen(filename, "r");

    if (fp == NULL) { exit(1); }                            // If file not found, exit with error

    while ((getline(&instruction, &len, fp)) != EOF) {      // While not at end of code generated
        // Determine next instruction
        if      (strcmp(instruction, "EXP\n") == 0) { operands[op-1] =   pow(operands[op-1], operands[op]); op--; }
        else if (strcmp(instruction, "MOD\n") == 0) { operands[op-1] = fmodf(operands[op-1], operands[op]); op--; }
        else if (strcmp(instruction, "ADD\n") == 0) { operands[op-1] =       operands[op-1] + operands[op]; op--; }
        else if (strcmp(instruction, "SUB\n") == 0) { operands[op-1] =       operands[op-1] - operands[op]; op--; }
        else if (strcmp(instruction, "MUL\n") == 0) { operands[op-1] =       operands[op-1] * operands[op]; op--; }
        else if (strcmp(instruction, "DIV\n") == 0) { operands[op-1] =       operands[op-1] / operands[op]; op--; }
        else {
            // Else we have a number and need to put into stack
            instruction[strcspn(instruction, "\n")] = 0;    // Removes newline character from instruction
            operands[++op] = strtof(instruction, NULL);
        }
    }
    free(instruction);
    fclose(fp);
    return operands[op];
}