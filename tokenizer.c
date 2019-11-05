// CS3500 Project - Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include "token.h"
#include "filedata.h"

#define BTSIZE 10                                                   // Memory allocation for single operand/operator size

// Formats file for conversion to tokens
filedata *parse_file(char *filename) {
    filedata *fd = create_filedata();
    FILE *fp = fopen(filename, "r");
    char c;
    int bp = -1;                                                    // Pointer to current position on buffer

    // If next char isn't EOF,
    //  decide if it should go on buffer or not
    while ((c = getc(fp)) != EOF) {
        switch (c) {
            case '\n':
            case ' ':
                break;
            default:
                fd->pstring[++bp] = c;

                // If operator, we need at least 2 more tokens
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                    fd->num_of_tokens += 2;
                }
        }
    }
    fd->num_of_tokens += 2;                                         // Used for last num & to indicate end of array
    return fd;
}

// Converts file to an array of tokens
token *convert_2_tokens(char *filename) {
    filedata *fd = parse_file(filename);

    char *buffer = malloc(BTSIZE);                                  // Buffer for current token
    int bp = -1;                                                    // Pointer to current position on buffer
    int pp = -1;                                                    // Pointer to current position on formatted string
    int isfloat = 0;                                                // Keeps track if buffer contains int or float
    token *cur_token;
    token *tokens = malloc(fd->num_of_tokens * sizeof(token));      // Array will need num of tokens * size of a token
    int tp = -1;                                                    // Pointer to current position on array of tokens

    while (fd->pstring[++pp] != '\0') {                             // While haven't reached end of string
        if (isdigit(fd->pstring[pp]) || fd->pstring[pp] == '.') {   // - If char is a digit or decimal point
            buffer[++bp] = fd->pstring[pp];                         // Put char into next position in buffer

            if (fd->pstring[pp] == '.') { isfloat = 1; }            // If char is a decimal point, buffer contains float

        } else {                                                    // - Else we have an operator
            if (isfloat)    { cur_token = create_token('f', buffer); }
            else            { cur_token = create_token('i', buffer); }
            tokens[++tp] = *cur_token;                              // Put token into next position in array

            // Value of token needs to be string, so this 'converts' single char to string
            char *op_val = malloc(1);
            op_val[0] = fd->pstring[pp];

            cur_token = create_token('o', op_val);
            tokens[++tp] = *cur_token;

            // Reset buffer and its related variables
            bp = -1; isfloat = 0;
            memset(buffer, 0, strlen(buffer));
        }
    }
    // Need to convert final number as operators are used as breakpoints, and there are no operators at end of string
    if (isfloat)    { cur_token = create_token('f', buffer); }
    else            { cur_token = create_token('i', buffer); }
    tokens[++tp] = *cur_token;

    return tokens;
}

// int main(int argc, char**argv) {
//     token *tokens = convert_2_tokens("input.txt");
//     print_token_array(tokens);
//     return 0;
// }
