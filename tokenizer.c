// CS3500 Project - Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>

#define BFSIZE 100                                                      // Memory allocation for full buffer size
#define OUTPUT_FILE "tokens.txt"
#define INPUT_FILE "input.txt"

// Prints formatted output to file
void write_file(char *output) {
    FILE *fp = NULL;
    if (fp = fopen(OUTPUT_FILE, "w"))   { fprintf(fp, "%s", output); fclose(fp); }
    else                                { fprintf(stderr, "Error: Could not create tokens.txt\n"); exit(4); }
}

// Marks end of operand and places operator in output
void end_of_token(int *new_num, char *output, int *op, char c, int* illegal_operator) {
    if (!*new_num) { output[++*op] = '\n'; }                            // Mark end of token by starting newline
    *new_num      = 1;                                                  // Next digit/decimal point will be a new num
    output[++*op] = 'o';                                                // Place operator in output
    output[++*op] = ',';
    output[++*op] = c;
    output[++*op] = '\n';
    *illegal_operator = 1;
}

// Reads in file & formats
char *parse_file(FILE *fp) {
    char *output = (char *)malloc(sizeof(char) * BFSIZE);               // Output used in I2P
    char c;                                                             // Current char in buffer
    int bp = -1;                                                        // Pointer to current position in buffer
    int op = -1;                                                        // Pointer to current position in output
    int new_num = 1;                                                    // Indicates if new num while processing buffer
    int illegal_operator = 1;                                           // Indicates if operator is valid as current char
    int num_is_neg = 0;                                                 // eg. 25 + -40 is a valid infix expression

    // If next char isn't EOF,
    //  decide if it should go on buffer or not
    while ((c = getc(fp)) != EOF) {
        switch (c) {
            case '\n':
            case ' ':
                break;
            case '(':
            case ')':
                end_of_token(&new_num, output, &op, c, &illegal_operator);
                if (c == ')') { illegal_operator = 0; }
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
                } else {
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
    return output;
}

// Converts file to an array of tokens
void convert_file_to_tokens(FILE *fp) {
    char *output = parse_file(fp);                                      // Read in file & format
    write_file(output);                                                 // Write out to tokens.txt
}

int main(int argc, char**argv) {
    FILE *fp = NULL;
    if (fp = fopen(INPUT_FILE, "r")) { convert_file_to_tokens(fp); }
    else                             { fprintf(stderr, "Error: input.txt doesn't exist\n"); return 1; }

    return 0;
}
