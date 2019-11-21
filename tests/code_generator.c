// CS3500 Project - Code Generator Tests
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade
// Author: Daniels Bindemans

#include "../src/code_generator.h"
#include <ctap.h>

TESTS {
    #define TEST_INPUT_FILE             "tests/i2p.txt"
    #define TEST_OUTPUT_FILE            "tests/code.txt"
    #define TEST_NO_INPUT_FILE          "tests/nofile.txt"
    #define TEST_INPUT                  "n,10\no,+\nn,5\no,/\nn,10\n"
    #define TEST_EXPECTED_OUTPUT        "10\nADD\n5\nDIV\n10\n"
    #define TEST_INVALID_OPERATOR_INPUT "n,10\no,$\nn,5\no,&\nn,10\n"
    #define TEST_INVALID_FORMAT_INPUT   "z,10\ny,+\nw,5\no,/\nn,10\n"

    // test inputs
    char test_inputs[3][30] = {
        TEST_INPUT,
        TEST_INVALID_FORMAT_INPUT,
        TEST_INVALID_OPERATOR_INPUT
    };
    // test messages
    char test_messages[3][40] = {
      "Correct input, Expected result correct",
      "Invalid file format",
      "Invalid operator inputs"
    };
    // test outputs
    char test_outputs[3][40] = {
      TEST_EXPECTED_OUTPUT,
      ERROR_INVALID_FILE_FORMAT,
      ERROR_INVALID_OPERAND
    };
    // test null file.
    is(generate_code(TEST_NO_INPUT_FILE), ERROR_NULL_INPUT, "No input file detected");

    for (int i = 0; i < 3; i++) {
        write_file(TEST_INPUT_FILE, test_inputs[i]);
        char *test_result = generate_code(TEST_INPUT_FILE);
        is(test_result, test_outputs[i], test_messages[i]);
    }

}
