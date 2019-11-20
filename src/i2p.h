// CS3500 Project - Infix To Postfix
// Conor Patrick Mc Donald
/*------------------------------DESCRIPTION---------------------------------------
i2p.c takes an input file consisting of infix expressions, converts to postfix format
and then outputs into a file called i2p.txt */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "write.h"
// #include <ctap.h>

#define INPUT_FILE "tokens.txt"
#define OUTPUT_FILE "output/i2p.txt"
#define ERROR_BAD_INPUT "Error: Input contained an invalid character \n"
#define ERROR_MISMATCHED_BRACKETS "Error: Uneven number of opening and closing brackets\n"
#define ERROR_EXPECTED_OPERATOR "Error: Expected operator after Operand or Opening Bracket\n"

/*---------------------------INPUT------------------------
*stack char



*/

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
  /*Exponent has highest precedence, Non operators(Numbers, brackets) have 0 precedence*/
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

// Writes operator onto output, in a CSV format
void push_operator(char *output, int *op, char *stack, int *top) {
    output[++*op] = 'o';
    output[++*op] = ',';
    output[++*op] = pop(stack, &*top);
    output[++*op] = '\n';
}

char *parse_file(FILE*fp){
    char *stack = (char *)malloc(100);  // The stack
    int top = -1; // initalise the top of stack
    char *chars;  //Input buffer Holds characters for getline()
    size_t len = 0; //Holds the size of the input buffer,
    char *output = (char *)malloc(400);
    int op = -1; // cursor to keep track of position in output array
    int lp = -1;  // Line pointer for characters in a current line
    char operator;

    while (getline(&chars, &len, fp) != EOF){
        char *s = strsep(&chars, ",");
        if (strcmp(s, "n") == 0) { // numbers are put directly into output queue in CSV format
            lp = -1;
            output[++op] = 'n';
            output[++op] = ',';

            while (chars[++lp] != '\0') { // Read to end of the line(value) e.g. 7.25\\0
                if (!isdigit(chars[lp])||chars[lp]=='.'){
                  return ERROR_BAD_INPUT;
                }
                output[++op] = chars[lp];
            }

        } else if (strcmp(s, "o") == 0){ //operands go straight to the stack
            s = strsep(&chars, ",");
            operator = s[0];
            if (operator == ')') {  // Must process what was between opening and closing brackets to keep correct precedence

                while(stack[top] != '(') { // Pop from stack til opening bracket found
                    if (stack[top] == '\0'){ // Have reached end without finding '('
                      return ERROR_MISMATCHED_BRACKETS; // Matching opening bracket not found
                    }
                    push_operator(output, &op, stack, &top);

                }
                pop(stack, &top); // Pops ( from stack

            } else if (operator == '(') {
                push(stack, &top, operator);

            } else { /*pop off all the operators that have same or higher precedence than cur operator to output*/
                while(precedence(stack[top]) >= precedence(operator)){
                    push_operator(output, &op, stack, &top);
                }
                push(stack, &top, operator);  // Place current operator on the stack
            }

        } else {
            return ERROR_BAD_INPUT;
        }
    }
    while (top != -1) { // Popping leftovers from stack
      if (stack[top] == '(' || ')'){ //shouldn't be any brackets on stack at this point
        return ERROR_MISMATCHED_BRACKETS;
      }
        push_operator(output, &op, stack, &top); // push to output
    }

    free(stack);
    fclose(fp);
    return output;
  }