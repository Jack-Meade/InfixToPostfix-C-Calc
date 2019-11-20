// CS3500 Project - VM
// Author: Jack Meade

#include "vm.h"

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
        else if (strcmp(instruction, "DIV\n") == 0) {
            // Cannot divide if second operand is 0
            if (operands[op] == 0)  { return ERROR_ZERO_DIV; }
            else                    { operands[op-1] = operands[op-1] / operands[op]; op--; }
        } else {                                                // Else we have a number and need to put into stack
            instruction[strcspn(instruction, "\n")] = 0;        // Removes newline character from instruction

            char c;
            char last_char;
            int i = -1;
            while ((c = instruction[++i]) != '\0') {
                if (((c < '0' || c > '9') && c != '.' && c != '-')  // not a digit/period/minus,
                    || (c == '.' && last_char == '.')               // two last chars are periods, or
                    || (c == '-' && last_char == '-')) {            // two last chars are minuses
                        return ERROR_INVALID_INST;
                    }
                last_char = c;
            }
            operands[++op] = strtof(instruction, NULL);
        }
    }
    free(instruction);
    fclose(fp);

    if (op != 0) { return ERROR_MISSING_INST; }                 // Result should be last in stack, missing needed inst
    // Convert result to string
    char *result = (char *)malloc(sizeof(char) * LENGTH_OF_RESULT);
    sprintf(result, "%4.4f", operands[op]);
    return result;
}
