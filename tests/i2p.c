// CS3500 Project - i2p Tests
// Author: Conor McDonald

#include "../src/i2p.h"
#include <ctap.h>

TESTS {
    // Defining test inputs/outputs to keep code cleaner
    #define TEST_INPUT_FILE         "tests/tokens.txt"
    #define TEST_EXPRESSION_INPUT   "n,10\no,+\nn,5\no,/\nn,10"
    #define TEST_EXPRESSION_OUTPUT  "n,10\no,+\nn,5\no,/\nn,10\n"
    #define TEST_OPERATOR_INPUT     "o,+"
    #define TEST_OPERATOR_OUTPUT    "o,+\n"
    #define TEST_EXTRA_OPERATOR     "n,5\no,+\no,+\nn,5\n"

    //output
    #define TEST_NO_INPUT           "tests/in.txt"
    #define TEST_BAD_INPUT          "10 +5/ c10"
    #define TEST_MISMATCHED_BRACKETS "o,(\no,(\no,)\n"
    #define TEST_MISSING_OPERATOR   "n,4\nn,5\nn,6\n"


    char *test_result;

    // Create test inputs
    char test_inputs[4][25] = {
        TEST_BAD_INPUT,
        TEST_MISMATCHED_BRACKETS,
        TEST_MISSING_OPERATOR,
        TEST_EXTRA_OPERATOR
    };

    // Create expected test outputs
    char test_outputs[4][80] = {
        ERROR_BAD_INPUT,
        ERROR_MISMATCHED_BRACKETS,
        ERROR_MISSING_OPERATOR,
        ERROR_TOO_MANY_OPERATORS
    };

    // Create test messages
    char test_messages[4][50] = {
        "Invalid character in input file",
        "Missing opening or closing bracket",
        "Missing operator after bracket",
        "Found 2 operators in a row"
    };

    // Need to test outside loop as it changes input file
    test_result = infix_to_postfix(TEST_NO_INPUT);
    is(test_result, ERROR_NO_INPUT_I2P, "Input file not found");

    // Go through test inputs, comparing result to expected output, and display descriptive message
    for (int i = 0; i < 4; i++) {
        write_file(TEST_INPUT_FILE, test_inputs[i]);
        test_result = infix_to_postfix(TEST_INPUT_FILE);
        is(test_result, test_outputs[i], test_messages[i]);
    }
}
