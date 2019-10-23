// CS3500 Tokenizer
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *parse_file(char *filename) {

}

int main(int argc, char**argv) {

	char buffer[201];
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

    printf("%s\n", buffer);
	return 0;
}
