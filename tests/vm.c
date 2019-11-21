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

    char test_inputs[7][30] = {
        TEST_ZERO_DIV,
        TEST_INVALID_INST1,
        TEST_MISSING_INST,
        TEST_INPUT
    };

    char test_outputs[7][40] = {
        ERROR_ZERO_DIV,
        ERROR_INVALID_INST,
        ERROR_MISSING_INST,
        TEST_OUTPUT
    };

    char test_messages[7][40] = {
        "Zero division in input file",
        "Incomplete instruction in input file",
        "Missing instruction in input file",
        "Able to execute instructions"
    };

    is(execute(TEST_NO_INPUT), ERROR_NO_INPUT_VM, "Input file not found");

    for (int i = 0; i < 4; i++) {
        write_file(TEST_INPUT_FILE, test_inputs[i]);
        test_result = execute(TEST_INPUT_FILE);
        is(test_result, test_outputs[i], test_messages[i]);
    }
}
