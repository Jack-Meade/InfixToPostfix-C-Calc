// CS3500 Project - Tokenizer
// Author: Jack Meade

#include "headers/tokenizer.h"

void end_of_token(int *new_num, char *output, int *op, char c, int *illegal_operator) {
    if (!*new_num) { output[++*op] = '\n'; }                            // Mark end of token by starting newline
    *new_num      = 1;                                                  // Next digit/decimal point will be a new num
    output[++*op] = 'o';                                                // Place operator in output
    output[++*op] = ',';
    output[++*op] = c;
    output[++*op] = '\n';
    *illegal_operator = 1;
}

char *convert_file_to_tokens(char *filename) {
    FILE *fp = NULL;
    if (!(fp = fopen(filename, "r"))) {                                 // If cannot open input file
        return ERROR_NO_INPUT_TOKEN;
    }
    char *output = (char *)malloc(sizeof(char) * BUFFER_SIZE);          // Output used in I2P
    char c;                                                             // Current character
    int op = -1;                                                        // Pointer to current position in output
    int new_num = 1;                                                    // Indicates if new num while processing buffer
    int illegal_operator = 1;                                           // Indicates if operator is valid as current char
    int num_is_neg = 0;                                                 // e.g 25 + -40 is a valid infix expression

    // If next char isn't EOF,
    //  decide if it should go in output or not
    while ((c = getc(fp)) != EOF) {
        switch (c) {
            case '\n': case ' ':                                        // Skip over newline and spaces
                break;

            case '(': case ')':                                         // Parentheses go straight to output
                end_of_token(&new_num, output, &op, c, &illegal_operator);
                if (c == ')') { illegal_operator = 0; }                 // e.g (2+3)^3 is a valid infix expression
                break;

            case '+': case '-': case '*':
            case '/': case '^': case '%':
                if (illegal_operator) {                                 // If operator shouldn't be current char
                    //  If the number is already defined as negative or the operator isn't a minus
                    if (num_is_neg || c != '-') {
                        fclose(fp);
                        return ERROR_INVALID_EXPRESSION;
                    } else {                                            // Else expression indicates number is negative
                        num_is_neg = 1;
                    }
                } else {                                                // Else put operator in output
                    end_of_token(&new_num, output, &op, c, &illegal_operator);
                    num_is_neg = 0;
                }
                break;

            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': case '.':
                if (new_num) {                                          //  If first char in new num
                    new_num      = 0;                                   //   Set it so next char won't be set as a new num
                    output[++op] = 'n';                                 //   Set it's type
                    output[++op] = ',';
                    if (num_is_neg) {                                   //  If number is negative
                        output[++op] = '-';                             //   Mark it as such
                        num_is_neg = 0;                                 //   Reset indicater
                    }
                }
                output[++op] = c;                                       // Place char in output
                illegal_operator = 0;                                   // An operator is legal after a num
                break;

            default:                                                    // Illegal character if not caught above
                fclose(fp);
                return ERROR_INVALID_CHAR;
        }
    }
    if (illegal_operator || output[op] == '.' ) {                       // If last char was an operator or period
        fclose(fp);
        return ERROR_TRAILING_OPERATOR;
    }
    fclose(fp);
    if (output[op] != '\n') {output[++op] = '\n';}                      // Adds newline if not at end of file
    return output;
}
