// CS3500 Project
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include "tokenizer.h"
#include "i2p.h"
#include "code_generator.h"
#include "vm.h"

int main(int argc, char**argv) {
    // Tokenizer
    char *output = convert_file_to_tokens(TOKEN_INPUT_FILE);             // Read in file & format
    if (strcmp(output, ERROR_NO_INPUT_TOKEN)     == 0 ||
        strcmp(output, ERROR_INVALID_EXPRESSION) == 0 ||
        strcmp(output, ERROR_TRAILING_OPERATOR)  == 0 ||
        strcmp(output, ERROR_INVALID_CHAR)       == 0) {
            fprintf(stderr, "Tokenizer: %s\n", output);
            return 1;
    } else {
        write_file(TOKEN_OUTPUT_FILE, output);
    }                   // Write tokens to output file

    // I2P
    output = infix_to_postfix(I2P_INPUT_FILE);
    if (strcmp(output, ERROR_NO_INPUT_I2P)        == 0 ||
        strcmp(output, ERROR_BAD_INPUT)           == 0 ||
        strcmp(output, ERROR_MISMATCHED_BRACKETS) == 0) {
            fprintf(stderr, "I2P: %s\n", output);
            return 1;
    }
    // Generate postfix from file
    write_file(I2P_OUTPUT_FILE, output);

    // Code Generator
    output = generate_code(CG_INPUT_FILE);      //parse the file
    write_file(CG_OUTPUT_FILE, output);         //write to new file the parsed data

    // VM
    char *result = execute(VM_INPUT_FILE);
    printf("%s\n", result);

    return 0;
}
