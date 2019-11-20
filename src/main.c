// CS3500 Project
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include "tokenizer.h"
// #include "i2p.h"
// #include "code_generator.h"
// #include "vm.h"

int main(int argc, char**argv) {
    // Tokenizer
    char *output = convert_file_to_tokens(INPUT_FILE);             // Read in file & format

    if      (strcmp(output, ERROR_NO_INPUT)           == 0) { fprintf(stderr, "Tokenizer: %s\n", ERROR_NO_INPUT);           return 1; }
    else if (strcmp(output, ERROR_INVALID_EXPRESSION) == 0) { fprintf(stderr, "Tokenizer: %s\n", ERROR_INVALID_EXPRESSION); return 1; }
    else if (strcmp(output, ERROR_TRAILING_OPERATOR)  == 0) { fprintf(stderr, "Tokenizer: %s\n", ERROR_TRAILING_OPERATOR);  return 1; }
    else if (strcmp(output, ERROR_INVALID_CHAR)       == 0) { fprintf(stderr, "Tokenizer: %s\n", ERROR_INVALID_CHAR);       return 1; }
    else    { write_file(OUTPUT_FILE, output); }                   // Write tokens to output file

    // Code Generator
    // char *str = parse_file(INPUT_FILE);      //parse the file
    // write_file(OUTPUT_FILE, str);            //write to new file the parsed data

    return 0;
}
