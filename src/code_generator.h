// CS3500 Project - Code Generator header
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade
// Author: Daniels Bindemans
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "write.h"

#define BUFFER_SIZE                 400
#define CG_INPUT_FILE               "output/i2p.txt"
#define CG_OUTPUT_FILE              "output/code.txt"

#define ERROR_INVALID_OPERAND       "Error: Invalid Operand\n"
#define ERROR_NULL_INPUT            "Error: Input file doesn't exist\n"
#define ERROR_INVALID_FILE_FORMAT   "Error: Invalid input format from file"
/*
parse_file
---DESCRIPTION---
Reads in file & creates formatted version as it goes through, line by line.

---INPUT---
*fp: pointer to file

---OUTPUT---
Formatted string:
-25
7.25
3
MUL
2
EXP
SUB
320
...
*/
char *generate_code(char *input_file);
