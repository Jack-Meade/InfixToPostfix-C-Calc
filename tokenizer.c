// CS3500 Project - Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.c"

#define BFSIZE 201
#define BTSIZE 10

char *parse_file(char *filename) {
    char *bufferf = malloc(BFSIZE);
    FILE *fp = fopen("input.txt", "r");
    char c = 0;
    int bp = 0;

    while ((c = getc(fp)) != EOF) {
        switch (c) {
            case '\n':
            case ' ':
                break;
            default:
                bufferf[bp] = c;
                bp ++;
        }
    }

    return bufferf;
}

int main(int argc, char**argv) {
    char *pstring = parse_file("input.text");
    printf("%s\n", pstring);

    char *buffert = malloc(BTSIZE);
    int bp = 0;
    int pp = 0;
    int isfloat = 0;

    while (pstring[pp] != EOF) {
        if (isdigit(pstring[pp]) || pstring[pp] == '.') {
            buffert[bp] = pstring[pp];
            pp ++; bp ++;

            if (pstring[pp] == '.') { isfloat = 1; }

            continue;
        } else {
            // TODO: when pstring[pp] is operator
        }
    }

	return 0;
}
