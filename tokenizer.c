// CS3500 Project - Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BFSIZE 101                                                  // Memory allocation for full buffer size

// Formats file
char *read_file(char *filename, char *component) {
    FILE *fp = fopen(filename, "r");
    char *buffer = malloc(sizeof(char) * BFSIZE);
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
                buffer[++bp] = c;
        }
    }
    return buffer;
}

void write_file(char *output) {
    FILE *fp = fopen("tokens.txt", "w");
    fprintf(fp, "%s", output);
}

// Converts file to an array of tokens
void convert_2_tokens(char *filename) {
    char *buffer = read_file(filename, "tokenizer");
    char *output = malloc(sizeof(char) * BFSIZE);

    int bp = -1;                                                    // Pointer to current position on buffer
    int op = -1;                                                    // Pointer to current position on output
    int new_num = 1;

    while (buffer[++bp] != '\0') {
        if (isdigit(buffer[bp]) || buffer[bp] == '.') {
            if (new_num) { new_num = 0; output[++op] = 'n'; output[++op] = ','; }
            output[++op] = buffer[bp];
        } else {
            output[++op] = '\n';
            new_num = 1;
            output[++op] = 'o';
            output[++op] = ',';
            output[++op] = buffer[bp];
            output[++op] = '\n';
        }
    }
    write_file(output);
}

int main(int argc, char**argv) {
    convert_2_tokens("input.txt");
    return 0;
}
