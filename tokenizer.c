// CS3500 Project - Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BFSIZE 101                                                  // Memory allocation for full buffer size
#define OUTPUT_FILE "tokens.txt"
#define INPUT_FILE "input.txt"

// Formats file
char *read_file(FILE *fp) {
    char *buffer = (char *)malloc(sizeof(char) * BFSIZE);
    char c;
    int bp = -1;                                                    // Pointer to current position on buffer
    int lastCharNotNum = 0;

    // If next char isn't EOF,
    //  decide if it should go on buffer or not
    while ((c = getc(fp)) != EOF) {
        switch (c) {
            case '\n':
            case ' ':
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '.':
                if (lastCharNotNum) {
                    fclose(fp);
                    fprintf(stderr, "Error: Invalid infix expression\n");
                    exit(2);
                }
                buffer[++bp] = c;
                lastCharNotNum = 1;
                break;
            default:
                buffer[++bp] = c;
                lastCharNotNum = 0;
        }
    }
    if (lastCharNotNum) {
        fclose(fp);
        fprintf(stderr, "Error: Trailing operator/period in expression\n");
        exit(3);
    }
    fclose(fp);
    return buffer;
}

// Prints output to file
void write_file(char *filename, char *output) {
    FILE *fp = NULL;                                                // Open/create file with write operations
    if (fp = fopen(filename, "w"))   { fprintf(fp, "%s", output); fclose(fp); }
    else                             { fprintf(stderr, "Error: Could not create tokens.txt\n"); exit(4); }

}

// Converts file to an array of tokens
void convert_file_to_tokens(FILE *fp) {
    char *buffer = read_file(fp);                                   // Read in formatted buffer
    char *output = (char *)malloc(sizeof(char) * BFSIZE);           // Output used in I2P

    int bp = -1;                                                    // Pointer to current position on buffer
    int op = -1;                                                    // Pointer to current position on output
    int new_num = 1;                                                // Indicates if new num while processing buffer

    while (buffer[++bp] != '\0') {                                  // While still have chars in buffer
        if (isdigit(buffer[bp]) || buffer[bp] == '.') {             // If char is a digit or decimal point
            if (new_num) {                                          //  If first char in new num
                new_num      = 0;                                   //   Set it so next char won't be set as a new num
                output[++op] = 'n';                                 //   Set it's type
                output[++op] = ',';                                 //   Seperate type from value
            }
            output[++op] = buffer[bp];                              //  Else, place char on buffer

        } else {                                                    // Else, we have an operator
            output[++op] = '\n';                                    // Mark end of token by starting newline
            new_num      = 1;                                       // Next digit/decimal point will be a new num
            output[++op] = 'o';                                     // Place operator on buffer, with type and value
            output[++op] = ',';
            output[++op] = buffer[bp];
            output[++op] = '\n';
        }
    }
    write_file(OUTPUT_FILE, output);                               // Write out to tokens.txt
    free(buffer);
    free(output);
}

int main(int argc, char**argv) {
    FILE *fp = NULL;
    if (fp = fopen(INPUT_FILE, "r")) { convert_file_to_tokens(fp); }
    else                              { fprintf(stderr, "Error: input.txt doesn't exist in this directory\n"); return 1; }

    return 0;
}
