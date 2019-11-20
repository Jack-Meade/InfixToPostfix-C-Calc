// CS3500 Project - VM Test Suite
// Author: Jack Meade

#include "../src/vm.h"
#include "../src/write.h"
#include <ctap.h>

TESTS {
    #define TEST_INPUT_FILE "tests/input.txt"
    #define TEST_INPUT      "-25\n7.25\n3\nMUL\nSUB\n"
    #define TEST_OUTPUT     "-46.7500"

    #define TEST_NO_INPUT       "tests/in.txt"
    #define TEST_INVALID_INST1  "-25\n7.25\n3\nMUL\nSU\n"
    #define TEST_INVALID_INST2  "-k5\n7.25\n3\nMUL\nSUB\n"
    #define TEST_INVALID_INST3  "-25\n7..25\n3\nMUL\nSUB\n"
    #define TEST_INVALID_INST4  "--25\n7.25\n3\nMUL\nSUB\n"
    #define TEST_ZERO_DIV       "-25\n0\nDIV\n"
    #define TEST_MISSING_INST   "-25\n7.25\n3\nMUL\n"

    char *test_result;

    char test_inputs[6][30] = {
        TEST_INVALID_INST1,
        TEST_INVALID_INST2,
        TEST_INVALID_INST3,
        TEST_INVALID_INST4,
        TEST_ZERO_DIV,
        TEST_MISSING_INST
    };

    char test_outputs[6][40] = {
        ERROR_INVALID_INST,
        ERROR_INVALID_INST,
        ERROR_INVALID_INST,
        ERROR_INVALID_INST,
        ERROR_ZERO_DIV,
        ERROR_MISSING_INST
    };

    char test_messages[6][40] = {
        "Incomplete instruction in input file",
        "Invalid number in input file",
        "Double period in input file",
        "Double negative in input file",
        "Zero division in input file",
        "Missing instruction in input file"
    };

    is(execute(TEST_NO_INPUT), ERROR_NO_INPUT, "Input file not found");
    write_file("buffer", TEST_ZERO_DIV);
    is(execute("buffer"), ERROR_ZERO_DIV, "Zero Div");
    // for (int i = 0; i < 6; i++) {
    //     char buffer[20];
    //     sprintf(buffer, "testfile%d", i);
    //     write_file(buffer, test_inputs[i]);
    //     test_result = execute(TEST_INPUT_FILE);
    //     is(test_result, test_outputs[i], test_messages[i]);
    // }
}
