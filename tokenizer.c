// CS3500 Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.c"

#define BSIZE 201

char *parse_file(char *filename) {
    char *buffer = malloc(BSIZE);
    FILE *fp = fopen("input.txt", "r");
    char c = 0;
    int bp = 0;

    while ((c = getc(fp)) != EOF) {
        switch (c) {
            case '\n':
            case ' ':
            case -1:
                break;
            default:
                buffer[bp] = c;
                bp ++;
        }

    }

    return buffer;
}

int main(int argc, char**argv) {
    char *pstring = parse_file("input.text");
    printf("%s\n", pstring);

    /* convert to tokens */

	return 0;
}
