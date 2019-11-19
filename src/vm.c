// CS3500 Project - VM
// Author: Jack Meade

#include "vm.h"

int main(int argc, char**argv) {
    char *result = execute(INPUT_FILE);
    printf("%s\n", result);
    return 0;
}
