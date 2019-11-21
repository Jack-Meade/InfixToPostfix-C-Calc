// CS3500 Project - Code Generator Tests
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade
// Author: Daniels Bindemans

#include "../src/code_generator.h"
#include <ctap.h>

TESTS {
    #define TEST_INPUT_FILE       "tests/i2p.txt"
    #define TEST_OUTPUT_FILE      "tests/code.txt"
    #define TEST_INPUT            "n,10\no,+\nn,5\no,/\nn,10\n"
    #define TEST_EXPECTED_OUTPUT  "10\nADD\n5\nDIV\n10\n"



    // write_file(TEST_INPUT_FILE, TEST_INPUT);
    // FILE *fp;
    // fp = fopen(TEST_INPUT_FILE, "w+");
    // fputs(TEST_INPUT, fp);
    // fclose(fp);
    //

   is(generate_code(TEST_INPUT_FILE), TEST_EXPECTED_OUTPUT, "result correct");
}
