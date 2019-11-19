// CS3500 Project - VM Header
// Author: Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACK_SIZE       200
#define LENGTH_OF_RESULT 100
#define INPUT_FILE       "output/code.txt"

#define ERROR_NO_INPUT      "Error: Cannot read input file\n"
#define ERROR_INVALID_NUM   "Error: Improper number instruction\n"

/*
---DESCRIPTION---
Executes VM using code from Code Generator.

---INPUT---
*filename:      string of file were code is located

---OUTPUT---
Result of calculation from instructions
*/
char *execute(char *filename) {
    FILE *fp;
    char *instruction;                                          // Buffer which holds current instruction
    float operands[STACK_SIZE];                                 // Operand stack
    int op = -1;                                                // Pointer to current operand in stack
    size_t len = 0;                                             // Pointer to size of buffer (needed for getline())

    if (!(fp = fopen(filename, "r"))) { return ERROR_NO_INPUT; }// If file not found, exit with error

    while ((getline(&instruction, &len, fp)) != EOF) {          // While not at end of code generated
        // Determine next instruction
        if      (strcmp(instruction, "EXP\n") == 0) { operands[op-1] =   pow(operands[op-1], operands[op]); op--; }
        else if (strcmp(instruction, "MOD\n") == 0) { operands[op-1] = fmodf(operands[op-1], operands[op]); op--; }
        else if (strcmp(instruction, "ADD\n") == 0) { operands[op-1] =       operands[op-1] + operands[op]; op--; }
        else if (strcmp(instruction, "SUB\n") == 0) { operands[op-1] =       operands[op-1] - operands[op]; op--; }
        else if (strcmp(instruction, "MUL\n") == 0) { operands[op-1] =       operands[op-1] * operands[op]; op--; }
        else if (strcmp(instruction, "DIV\n") == 0) { operands[op-1] =       operands[op-1] / operands[op]; op--; }
        else {                                                  // Else we have a number and need to put into stack
            instruction[strcspn(instruction, "\n")] = 0;        // Removes newline character from instruction

            // Error checking for valid number instruction
            char digit;
            int i = -1;
            while ((digit = instruction[++i]) != '\0') {
                // If digit is not a digit, period, or minus, it is not part of a vaild number
                if ((digit < '0' || digit > '9') && digit != '.' && digit != '-') { return ERROR_INVALID_NUM; }
            }
            operands[++op] = strtof(instruction, NULL);
        }
    }
    free(instruction);
    fclose(fp);

    // Convert result to string
    char *result = (char *)malloc(sizeof(char) * LENGTH_OF_RESULT);
    sprintf(result, "%4.4f", operands[op]);
    return result;
}
