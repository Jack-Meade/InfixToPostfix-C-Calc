// CS3500 Project - Tokenizer
// Author: Jack Meade

#include "tokenizer.h"

int main(int argc, char**argv) {
    char *output = convert_file_to_tokens(INPUT_FILE);             // Read in file & format

    if      (strcmp(output, ERROR_NO_INPUT)           == 0) { fprintf(stderr, "%s\n", ERROR_NO_INPUT);           return 1; }
    else if (strcmp(output, ERROR_INVALID_EXPRESSION) == 0) { fprintf(stderr, "%s\n", ERROR_INVALID_EXPRESSION); return 1; }
    else if (strcmp(output, ERROR_TRAILING_OPERATOR)  == 0) { fprintf(stderr, "%s\n", ERROR_TRAILING_OPERATOR);  return 1; }
    else if (strcmp(output, ERROR_INVALID_CHAR)       == 0) { fprintf(stderr, "%s\n", ERROR_INVALID_CHAR);       return 1; }
    else    { write_file(OUTPUT_FILE, output); }                   // Write tokens to output file
    return 0;
}
