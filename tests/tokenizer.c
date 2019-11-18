// CS3500 Project - Tokenizer Test Suite
// Author: Jack Meade

#include "src/tokenizer.h"

TESTS {
    #define TEST_INPUT_FILE         "tests/input.txt"
    #define TEST_INPUT_EXPRESSION   "10 +5/ 10"
    #define TEST_OUTPUT_EXPRESSION  "n,10\no,+\nn,5\no,/\nn,10\n"

    char *line;
    size_t len;
    write_file(TEST_INPUT_FILE, TEST_INPUT_EXPRESSION);
    FILE *fp1 = fopen(TEST_INPUT_FILE, "r");
    isnt_null(fp1,                  "Able to read files");
    getline(&line, &len, fp1);
    is(line, TEST_INPUT_EXPRESSION, "Able to write files");

    FILE *fp2 = fopen(TEST_INPUT_FILE, "r");
    char *test_output = parse_file(fp2);
    is(test_output, TEST_OUTPUT_EXPRESSION, "Able to tokenize input file");
}
