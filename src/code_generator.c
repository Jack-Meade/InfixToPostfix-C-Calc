#include "code_generator.h"

int main(int argc, char**argv) {
    FILE *fp = NULL;
    if (!(fp = fopen(INPUT_FILE, "r"))){         //Try to open file if file is null
        printf("%s\n",INPUT_FILE );
        printf("%s\n",ERROR_NULL_INPUT);
        return 1;                             //Then the file doesn't exist
    }

    char *str = parse_file(fp);              //parse the file
    write_file(OUTPUT_FILE, str);            //write to new file the parsed data
    return 0;
}
