#ifndef TOKEN_H
#define TOKEN_H
// CS3500 Project - Tokenizer Header
// Author: Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include "write.h"
#include <string.h>

#define BUFFER_SIZE 400                                                 // Memory allocation for full buffer size
#define TOKEN_INPUT_FILE  "input.txt"
#define TOKEN_OUTPUT_FILE "output/tokens.txt"

#define ERROR_NO_INPUT_TOKEN        "Error: Cannot read input file\n"
#define ERROR_INVALID_EXPRESSION    "Error: Invalid infix expression\n"
#define ERROR_INVALID_CHAR          "Error: Invalid character in expression\n"
#define ERROR_TRAILING_OPERATOR     "Error: Trailing operator/period in expression\n"

/* end_of_token()
---DESCRIPTION---
Marks end of token and places operator in output.

---INPUT---
*new_num:           pointer to boolean if token is start of new num
*output:            formatted output string to be used in I2P
*op:                pointer to current position on output string
 c:                 current character in file
*illegal_operator:  pointer to boolean if character is allowed to be operator
*/
void end_of_token(int *new_num, char *output, int *op, char c, int *illegal_operator);

/* convert_file_to_tokens()
---DESCRIPTION---
Reads in file & creates formatted version as it goes through, character by character.

---INPUT---
*filename:                string to locate input file

---OUTPUT---
Error message or formatted string representing tokens, e.g:
n,25
o,+
n,12.5

*/
char *convert_file_to_tokens(char *filename);

#endif
