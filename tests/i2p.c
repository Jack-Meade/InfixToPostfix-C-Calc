// CS3500 Project - i2p Tests
// Author: Conor McDonald

#include "../src/i2p.h"
#include <ctap.h>

TESTS {
    // Defining test inputs/outputs to keep code cleaner
    #define TEST_INPUT_FILE         "tests/tokens.txt"
    #define TEST_EXPRESSION_INPUT   "10+5/10"
    #define TEST_EXPRESSION_OUTPUT  "n,10\no,+\nn,5\no,/\nn,10\n"
    #define TEST_OPERATOR_INPUT     '+'
    #define TEST_OPERATOR_OUTPUT    "o,+\n"
    #define TEST_EXTRA_OPERATOR     "5++5*/7"

    //output
    #define TEST_NO_INPUT           "tests/in.txt"
    #define TEST_BAD_INPUT          "10 +5/ c10"
    #define TEST_MISMATCHED_BRACKETS "5 +(2+4))"
    #define TEST_MISSING_OPERATOR   "456"


    char *test_result;

    // Create test inputs
    char test_inputs[4][15] = {
        TEST_BAD_INPUT,
        TEST_MISMATCHED_BRACKETS,
        TEST_MISSING_OPERATOR,
        TEST_EXTRA_OPERATOR
    };

    // Create expected test outputs
    char test_outputs[4][50] = {
        ERROR_BAD_INPUT,
        ERROR_MISMATCHED_BRACKETS,
        ERROR_MISSING_OPERATOR,
        ERROR_TOO_MANY_OPERATORS
    };

    // Create test messages
    char test_messages[4][50] = {
        "Invalid character in input file",
        "Missing opening or closing bracket"
        "Missing operator after bracket"
        "Found 2 operators in a row"
    };

    // Need to test outside loop as it changes input file
    test_result = parse_file(TEST_NO_INPUT);
    is(test_result, ERROR_NO_INPUT, "Input file not found");

    // Go through test inputs, comparing result to expected output, and display descriptive message
    for (int i = 0; i < 2; i++) {
        write_file(TEST_INPUT_FILE, test_inputs[i]);
        test_result = parse_file(TEST_INPUT_FILE);
        is(test_result, test_outputs[i], test_messages[i]);
    }
}
