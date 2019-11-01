// CS3500 Project - Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.c"

#define BFSIZE 201
#define BTSIZE 10

char *parse_file(char *filename) {
    char *buffer = malloc(BFSIZE);
    FILE *fp = fopen("input.txt", "r");
    char c = 0;
    int bp = 0;

    while ((c = getc(fp)) != EOF) {
        switch (c) {
            case '\n':
            case ' ':
                break;
            default:
                buffer[bp] = c;
                bp ++;
        }
    }

    return buffer;
}

char *convert_2_tokens() {

}

int main(int argc, char**argv) {
    char *pstring = parse_file("input.text");
    printf("%s\n", pstring);

    char *buffer = malloc(BTSIZE);
    int bp = 0;
    int pp = 0;
    int isfloat = 0;
    char type;
    token *tokens = malloc(BFSIZE * sizeof(token));
    int tp = 0;

    while (pstring[pp] != '\0') {
        if (isdigit(pstring[pp]) || pstring[pp] == '.') {
            buffer[bp] = pstring[pp];
            pp ++; bp ++;

            if (pstring[pp] == '.') { isfloat = 1; }

            continue;
        } else {
            if (isfloat)    { type = 'f'; }
            else            { type = 'i'; }

            token *tokenNum = create_token(type, buffer);
            tokens[tp] = *tokenNum;
            tp ++;

            token *tokenOp = create_token(pstring[pp], "op");
            tokens[tp] = *tokenOp;

            tp ++; pp ++; bp = 0;
            memset(buffer,0,strlen(buffer));
            continue;
        }

    }
    if (isfloat)    { type = 'f'; }
    else            { type = 'i'; }

    token *tokenNum = create_token(type, buffer);
    tokens[tp] = *tokenNum;

    while (tp) {
        printToken(&tokens[tp]);
        tp --;
    } printToken(&tokens[tp]);

	return 0;
}
