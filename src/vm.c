// CS3500 Project - VM
// Author: Jack Meade

#include "vm.h"

int main(int argc, char**argv) {
    float result = execute(INPUT_FILE);
    printf("%4.4f\n", result);
    return 0;
}
