// CS3500 Project - Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BFSIZE 101                                                  // Memory allocation for full buffer size
#define OUTPUT_FILE "tokens.txt"
#define INPUT_FILE "input.txt"

// Prints formatted output to file
void write_file(char *output) {
    FILE *fp = NULL;
    if (fp = fopen(OUTPUT_FILE, "w"))   { fprintf(fp, "%s", output); fclose(fp); }
    else                             { fprintf(stderr, "Error: Could not create tokens.txt\n"); exit(4); }
}

// Reads in file & formats
char *parse_file(FILE *fp) {
    char *output = (char *)malloc(sizeof(char) * BFSIZE);           // Output used in I2P
    char c;
    int bp = -1;                                                    // Pointer to current position on buffer
    int op = -1;                                                    // Pointer to current position on output
    int new_num = 1;                                                // Indicates if new num while processing buffer
    int lastCharNotNum = 1;
    int num_is_neg = 0;

    // If next char isn't EOF,
    //  decide if it should go on buffer or not
    while ((c = getc(fp)) != EOF) {
        switch (c) {
            case '\n':
            case ' ':
                break;
            case '(':
            case ')':
                if (!new_num) { output[++op] = '\n'; }                  // Mark end of token by starting newline
                new_num      = 1;                                       // Next digit/decimal point will be a new num
                output[++op] = 'o';                                     // Place operator on buffer, with type and value
                output[++op] = ',';
                output[++op] = c;
                output[++op] = '\n';
                lastCharNotNum = 1;
                if (c == ')') { lastCharNotNum = 0; }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                if (lastCharNotNum) {
                    if (num_is_neg || c != '-') {
                        fclose(fp);
                        fprintf(stderr, "Error: Invalid infix expression\n");
                        exit(2);
                    } else {
                        num_is_neg = 1;
                    }
                } else {
                    if (!new_num) { output[++op] = '\n'; }                  // Mark end of token by starting newline
                    new_num      = 1;                                       // Next digit/decimal point will be a new num
                    output[++op] = 'o';                                     // Place operator on buffer, with type and value
                    output[++op] = ',';
                    output[++op] = c;
                    output[++op] = '\n';
                    lastCharNotNum = 1;
                    num_is_neg = 0;

                }
                break;
            default:
                if (new_num) {                                          //  If first char in new num
                    new_num      = 0;                                   //   Set it so next char won't be set as a new num
                    output[++op] = 'n';                                 //   Set it's type
                    output[++op] = ',';
                    if (num_is_neg) {
                        output[++op] = '-';
                    }
                }
                output[++op] = c;
                lastCharNotNum = 0;
                num_is_neg = 0;
        }
    }
    if (lastCharNotNum) {
        fclose(fp);
        fprintf(stderr, "Error: Trailing operator/period in expression\n");
        exit(3);
    }
    fclose(fp);
    return output;
}

// Converts file to an array of tokens
void convert_file_to_tokens(FILE *fp) {
    char *output = parse_file(fp);                                  // Read in file & format
    write_file(output);                                // Write out to tokens.txt
}

int main(int argc, char**argv) {
    FILE *fp = NULL;
    if (fp = fopen(INPUT_FILE, "r")) { convert_file_to_tokens(fp); }
    else                             { fprintf(stderr, "Error: input.txt doesn't exist\n"); return 1; }

    return 0;
}
