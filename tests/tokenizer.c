// CS3500 Project - Tokenizer Test Suite
// Author: Jack Meade

#include "../src/tokenizer.h"
#include <ctap.h>

TESTS {
    // Defining test inputs/outputs to keep code cleaner
    #define TEST_INPUT_FILE         "tests/input.txt"
    #define TEST_EXPRESSION_INPUT   "10 +5/ 10"
    #define TEST_EXPRESSION_OUTPUT  "n,10\no,+\nn,5\no,/\nn,10\n"
    #define TEST_OPERATOR_INPUT     '+'
    #define TEST_OPERATOR_OUTPUT    "o,+\n"

    #define TEST_NO_INPUT           "tests/in.txt"
    #define TEST_INVALID_CHAR       "10 +5/ c10"
    #define TEST_TRAILING_OPERATOR  "10 +5/ 10^"
    #define TEST_TRAILING_PERIOD    "10 +5/ 10."
    #define TEST_INVALID_EXPRESSION "10 +5-/ 10"

    char *test_result;

    // Create test inputs
    char test_inputs[5][15] = {
        TEST_INVALID_EXPRESSION,
        TEST_INVALID_CHAR,
        TEST_TRAILING_OPERATOR,
        TEST_TRAILING_PERIOD,
        TEST_EXPRESSION_INPUT
    };

    // Create expected test outputs
    char test_outputs[5][50] = {
        ERROR_INVALID_EXPRESSION,
        ERROR_INVALID_CHAR,
        ERROR_TRAILING_OPERATOR,
        ERROR_TRAILING_OPERATOR,
        TEST_EXPRESSION_OUTPUT
    };

    // Create test messages
    char test_messages[5][50] = {
        "Invalid expression in input file",
        "Invalid character in input file",
        "Trailing operator in input file",
        "Trailing period in input file",
        "Able to tokenize input file"
    };

    // Need to test outside loop as it changes input file
    test_result = convert_file_to_tokens(TEST_NO_INPUT);
    is(test_result, ERROR_NO_INPUT, "Input file not found");

    // Go through test inputs, comparing result to expected output, and display descriptive message
    for (int i = 0; i < 5; i++) {
        write_file(TEST_INPUT_FILE, test_inputs[i]);
        test_result = convert_file_to_tokens(TEST_INPUT_FILE);
        is(test_result, test_outputs[i], test_messages[i]);
    }

    // Testing if token can be properly marked
    int new_num          = 1;
    test_result          = (char *)malloc(5);
    int op               = -1;
    char c               = TEST_OPERATOR_INPUT;
    int illegal_operator = 0;

    end_of_token(&new_num, test_result, &op, c, &illegal_operator);
    is(test_result, TEST_OPERATOR_OUTPUT, "Able to mark end of tokens");

}
