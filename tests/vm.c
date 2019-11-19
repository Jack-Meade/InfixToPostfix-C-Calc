// CS3500 Project - VM Test Suite
// Author: Jack Meade

#include "../src/vm.h"
#include "../src/write.h"
#include <ctap.h>

TESTS {
    #define TEST_INPUT_FILE "tests/input.txt"
    #define TEST_INPUT      "-25\n7.25\n3\nMUL\nSUB\n"
    #define TEST_OUTPUT     -46.75

    write_file(TEST_INPUT_FILE, TEST_INPUT);
    ok(TEST_OUTPUT == execute(TEST_INPUT_FILE), "Able to execute instructions");
}
