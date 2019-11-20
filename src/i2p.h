// CS3500 Project - Infix To Postfix
// Conor Patrick Mc Donald
/*------------------------------DESCRIPTION---------------------------------------
i2p.c takes an input file consisting of infix expressions, converts to postfix format
and then outputs into a file called i2p.txt */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "write.h"

#define I2P_INPUT_FILE "output/tokens.txt"
#define I2P_OUTPUT_FILE "output/i2p.txt"
#define ERROR_NO_INPUT_I2P "Error: Couldn't open input file\n"
#define ERROR_BAD_INPUT "Error: Input contained an invalid character\n"
#define ERROR_MISMATCHED_BRACKETS "Error: Uneven number of opening and closing brackets\n"
#define ERROR_EXPECTED_OPERATOR "Error: Expected operator after Operand or Opening Bracket\n"

/*---------------------------INPUT------------------------
*stack char



*/
char pop(char *stack, int *top);

void push(char *stack, int *top, char x);

int precedence(char x);

// Writes operator onto output, in a CSV format
void push_operator(char *output, int *op, char *stack, int *top);

char *infix_to_postfix(char *filename);
