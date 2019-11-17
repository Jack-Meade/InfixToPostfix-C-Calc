// CS3500 Project - Infix To Postfix
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prints formatted output to file
void write_file(char *output) {
    FILE *fp = NULL;
    if (fp = fopen("i2p.txt", "w"))     { fprintf(fp, "%s", output); fclose(fp); }
    else                                { fprintf(stderr, "Error: Could not create i2p.txt\n"); exit(1); }
}

/*Pop the top object off the tack and return it*/
char pop(char *stack, int *top) {
    char top_of_stack = stack[*top];
    stack[*top]= '\0';
    --*top;
    return top_of_stack;  // Return what what the top of stack and decrement stack cursor by 1
}

void push(char *stack, int *top, char x){ // Add next char to top of stack
    stack[++*top] = x; // Inc the stack cursor by 1
}

int precedence(char x){
    switch(x) {
        case '^':
            return 3; break;

        case '*': case '/': case '%':
            return 2; break;

        case '+': case '-':
            return 1; break;

        default:
            return 0;
    }
}

// Writes operator onto output
void push_operator(char *output, int *op, char *stack, int *top) {
    output[++*op] = 'o';
    output[++*op] = ',';
    output[++*op] = pop(stack, &*top);
    output[++*op] = '\n';
}

char *parse_file(FILE*fp){
    char *stack = (char *)malloc(100);  // The stack
    int top = -1; // initalise the top of stack
    char *chars;                    //Input buffer Holds characters for getline()
    size_t len = 0;                 //Holds the size of the input buffer,
    char *output = (char *)malloc(400);
    int op = -1;
    int lp = -1;
    char operator;

    while (getline(&chars, &len, fp) != EOF){
        char *s = strsep(&chars, ",");
        if (strcmp(s, "n") == 0) { // numbers are put directly into output queue
            lp = -1;
            output[++op] = 'n';
            output[++op] = ',';

            while (chars[++lp] != '\0') {
                output[++op] = chars[lp];
            }

        } else if (strcmp(s, "o") == 0){ //operands go straight to the stack
            s = strsep(&chars, ",");
            operator = s[0];

            if (operator == ')') {
                while(stack[top] != '(') { // Pop from stack til opening bracket found
                    push_operator(output, &op, stack, &top);
                }
                pop(stack, &top); // Pops ( from stack

            } else if (operator == '(') {
                push(stack, &top, operator);

            } else {
                while(precedence(stack[top]) >= precedence(operator)){
                    push_operator(output, &op, stack, &top);
                }
                push(stack, &top, operator);
            }

        } else { // Otherwise it is a number
            printf("Bad input\n");
        }
    }
    while (top != -1) { // Popping leftovers from stack
        push_operator(output, &op, stack, &top);
    }

    free(stack);
    fclose(fp);
    return output;
  }

int main(int argc, char const *argv[]) {
    //opening the file
    FILE *fp = NULL;
    fp = fopen("tokens.txt","r");
    if (fp == NULL){
        fprintf(stderr, "File does not exist.\n");
        return 1;
    }
    // Generate postfix from file
    write_file(parse_file(fp));
}
