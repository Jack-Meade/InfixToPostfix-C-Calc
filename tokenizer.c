// CS3500 Tokenizer
// Conor Patrick Mc Donald, Daniels Bindemans, Jack Meade

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char**argv) {

	char buffer[1000];
	FILE *fp = fopen("input.txt", "r");
    int bp = 0;

    while (buffer[bp] != '\0') {
        buffer[bp] = getc(fp);
        bp ++;
    }

    buffer[bp] = getc(fp);
    printf("%s\n", buffer);
	return 0;
}
