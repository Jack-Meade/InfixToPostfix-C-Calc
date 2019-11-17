// CS3500 Project - VM
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include <ctap.h>

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

int main(int argc, char**argv) {
    float result = execute(INPUT_FILE);
    printf("%4.4f\n", result);
    return 0;
}

// Test suite
// TESTS {
//     #include "write.h"
//     #define TEST_INPUT_FILE "tests/input.txt"
//     #define TEST_INPUT_CODE "-25\n7.25\n3\nMUL\nSUB\n"
//
//     ok(STACK_SIZE == 200,               "Buffer size set correct");
//     ok(INPUT_FILE == "output/code.txt", "Input file set correct");
//
//     char *line;
//     size_t len;
//     write_file(TEST_INPUT_FILE, TEST_INPUT_CODE);
//     FILE *fp1 = fopen(TEST_INPUT_FILE, "r");
//     isnt_null(fp1,            "Able to read files");
//     ok(-46.75 == execute(TEST_INPUT_FILE), "Able to execute instructions");
// }
