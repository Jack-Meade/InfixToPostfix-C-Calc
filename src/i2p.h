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
#define ERROR_MISMATCHED_BRACKETS "Error: Uneven number of ( and )\n"
#define ERROR_EXPECTED_OPERATOR "Error: Expected operator after Operand or Opening Bracket\n"
#define ERROR_MISSING_OPERATOR "Error: Expected operator after number\n"
#define ERROR_TOO_MANY_OPERATORS "Error: Operator immediately followed by another operator"

/*--DESCRIPTION--
// Removes the top char from the stack and returns it.
   Stack point (top) decremented by 1
--INPUT--
*stack char
*top int Keeps track of top of stack

--OUTPUT--
char

*/
char pop(char *stack, int *top);



/*--DESCRIPTION--
//
--INPUT--
*stack char
*top int Keeps track of top of stack
char x - character to be placed on top of stack
*/
void push(char *stack, int *top, char x);

/*--DESCRIPTION--
Determines the precedence of a given operator
--INPUT--
char x
--OUTPUT--
int between 0(lowest) and 3(highest)
*/
int precedence(char x);


/*--DESCRIPTION--
Writes operator onto output, in a CSV format
*/
void push_operator(char *output, int *op, char *stack, int *top);



/*--DESCRIPTION--
// Reads in a file(tokens.txt) character by character and processes the infix expression to
postfix expression and then returns the finished postfix expression as array.
--INPUT--
*fp Pointer to the input file

--OUTPUT--
char array of postfix expression is returned

*/
char *infix_to_postfix(char*filename);
