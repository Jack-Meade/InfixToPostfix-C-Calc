// CS3500 Project - Code Generator Tests
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade
// Author: Daniels Bindemans

#include "../src/code_generator.c"
#include <ctap.h>

TESTS {
    #define TEST_INPUT_FILE       "../tests/i2p.txt"
    #define TEST_OUTPUT_FILE      "../tests/code.txt"
    #define TEST_INPUT            "n,10\no,+\nn,5\no,/\nn,10\n"
    #define TEST__EXPECTED_OUTPUT "10\nADD\n5\nDIV\n10\n"

    write_file(TEST_INPUT_FILE, TEST_INPUT);
    char* result = parse_file(TEST_INPUT_FILE);
    diag("%s\n", result );
    is(result, TEST__EXPECTED_OUTPUT, "Expected result correct");
}
