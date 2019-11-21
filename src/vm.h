#ifndef VM_H
#define VM_H
// CS3500 Project - VM Header
// Author: Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STACK_SIZE       200
#define LENGTH_OF_RESULT 100
#define VM_INPUT_FILE       "output/code.txt"

#define ERROR_NO_INPUT_VM   "Error: Cannot read input file\n"
#define ERROR_INVALID_INST  "Error: Invalid instruction\n"
#define ERROR_ZERO_DIV      "Error: Cannot divide by zero\n"
#define ERROR_MISSING_INST  "Error: Could not complete calculation\n"

/*
---DESCRIPTION---
Executes VM using code from Code Generator.

---INPUT---
*filename:      string of file were code is located

---OUTPUT---
Result of calculation from instructions
*/
char *execute(char *filename);

#endif
