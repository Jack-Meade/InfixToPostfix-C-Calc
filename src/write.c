// CS3500 Project - Write
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include "headers/write.h"

void write_file(char *output_file, char *output) {
    FILE *fp = NULL;
    if ((fp = fopen(output_file, "w")))   { fprintf(fp, "%s", output); fclose(fp); }
    else                                  { fprintf(stderr, "Error: Could not create %s\n", output_file); exit(1); }
}
