// CS3500 Project - Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include "write.h"
// #include <ctap.h>

#define BUFFER_SIZE 400                                                 // Memory allocation for full buffer size
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output/tokens.txt"

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
void end_of_token(int *new_num, char *output, int *op, char c, int *illegal_operator) {
    if (!*new_num) { output[++*op] = '\n'; }                            // Mark end of token by starting newline
    *new_num      = 1;                                                  // Next digit/decimal point will be a new num
    output[++*op] = 'o';                                                // Place operator in output
    output[++*op] = ',';
    output[++*op] = c;
    output[++*op] = '\n';
    *illegal_operator = 1;
}

/* parse_file()
---DESCRIPTION---
Reads in file & creates formatted version as it goes through, character by character.

---INPUT---
*fp:                pointer to file

---OUTPUT---
Formatted string representing tokens, e.g:
n,25
o,+
n,12.5
*/
char *parse_file(FILE *fp) {
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
            case '\n':
            case ' ':
                break;
            case '(':
            case ')':                                                   // Parentheses go straight to output
                end_of_token(&new_num, output, &op, c, &illegal_operator);
                if (c == ')') { illegal_operator = 0; }                 // e.g (2+3)^3 is a valid infix expression
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '%':
                if (illegal_operator) {                                 // If operator shouldn't be current char
                    //  If the number is already defined as negative or the operator isn't a minus
                    if (num_is_neg || c != '-') {
                        fclose(fp);
                        fprintf(stderr, "Error: Invalid infix expression\n");
                        exit(2);
                    } else {                                            // Else expression indicates number is negative
                        num_is_neg = 1;
                    }
                } else {                                                // Else put operator in output
                    end_of_token(&new_num, output, &op, c, &illegal_operator);
                    num_is_neg = 0;

                }
                break;
            default:
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
        }
    }
    if (illegal_operator || output[op] == '.' ) {                       // If last char was an operator or period
        fclose(fp);
        fprintf(stderr, "Error: Trailing operator/period in expression\n");
        exit(3);
    }
    fclose(fp);
    output[++op] = '\n';
    return output;
}

/* convert_file_to_tokens()
---DESCRIPTION---
Converts file to an array of tokens.

---INPUT---
*fp:                pointer to file
*/
void convert_file_to_tokens(FILE *fp) {
    char *output = parse_file(fp);                                      // Read in file & format
    write_file(OUTPUT_FILE, output);                                    // Write out to tokens.txt
}

int main(int argc, char**argv) {
    FILE *fp = NULL;
    if (fp = fopen(INPUT_FILE, "r")) { convert_file_to_tokens(fp); }
    else                             { fprintf(stderr, "Error: input.txt doesn't exist\n"); return 1; }

    return 0;
}

// Test suite
// TESTS {
//     #define TEST_INPUT_FILE         "tests/test_tokenizer_input.txt"
//     #define TEST_INPUT_EXPRESSION   "10 +5/ 10"
//     #define TEST_OUTPUT_EXPRESSION  "n,10\no,+\nn,5\no,/\nn,10\n"
//
//     ok(BUFFER_SIZE == 400,                   "Buffer size set correct");
//     ok(INPUT_FILE  == "input.txt",           "Input file set correct");
//     ok(OUTPUT_FILE == "output/tokens.txt",   "Output file set correct");
//
//     char *line;
//     size_t len;
//     write_file(TEST_INPUT_FILE, TEST_INPUT_EXPRESSION);
//     FILE *fp1 = fopen(TEST_INPUT_FILE, "r");
//     getline(&line, &len, fp1);
//     is(line, TEST_INPUT_EXPRESSION, "Able to read/write files");
//
//     FILE *fp2 = fopen(TEST_INPUT_FILE, "r");
//     char *test_output = parse_file(fp2);
//     is(test_output, TEST_OUTPUT_EXPRESSION, "Able to tokenize input file");
// }
