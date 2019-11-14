#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*Pop the top object off the tack and return it*/
char pop(char *stack, int *top){
  if(*top == -1)  // Stack is empty so return -1
      return '?';
  else
    printf("%c\n", stack[*top-1]);
      return stack[*top--];  // Return what what the top of stack and decrement stack cursor by 1
}

void push(char *stack, int *top, char x){ // Add next char to top of stack
  stack[++*top] = x; // Inc the stack cursor by 1
}

int precedence(char x){
  if(x == '^'){  // Exponent has the highest priority
    return 3;
  }

  else if(x == '*' || x == '/' || x == '%'){  // Multiplication and Division/Modulo have second Highest
      return 2;
  }

  else if(x == '+' || x == '-'){  // Addition and subtraction have third highest priority(1)
      return 1;
  }
  else{  // Brackets have a priority of 0
      return 0;
  }

}

char *parse_file(FILE*fp){
    char *stack = (char *)malloc(100);  // The stack, 60 bytes
    int top = -1; // initalise the top of stack
    char *chars;                    //Input buffer Holds characters for getline()
    size_t len = 0;                 //Holds the size of the input buffer,
    char *output = (char *)malloc(100);
    int i=-1;
    int lp=-1;
    char op;
    char val;
    while (getline(&chars, &len, fp) != EOF){
        char *s = strsep(&chars, ",");
        if (strcmp(s, "n") == 0) { // numbers are put directly into output queue
          lp = -1;
          output[++i] = 'n';
          output[++i] = ',';
          while (chars[++lp] != '\0') {
            output[++i] = chars[lp];
          }
          printf("%s\n", output);
        }
        else if (strcmp(s, "o") == 0){

            // printf("%s\n", s);
            s = strsep(&chars, ",");  //operands go straight to the stack
            s[strcspn(s, "\n")] = 0;
            op = s[0];
            if (op == ')')    {
                while(val = pop(stack, &top) != '('){
                  output[++i] = 'o';
                  output[++i] = ',';
                  output[++i] = val;
                  output[++i] = '\n';
                  //printf("%c\n", val);
                }
            }
            else if (op == '(') {push(stack, &top, op);}
            else {
              while(top != -1 && precedence(stack[top]) >= precedence(op)){
                output[++i] = 'o';
                output[++i] = ',';
                output[++i] = pop(stack, &top);
                output[++i] = '\n';
              }
              push(stack, &top, op);
              printf("%s\n", "poppop");
            }
        }
        else {
          printf("Bad input\n");
        }  // Otherwise it is a number


    }
    printf("%s\n",output );
  }

    int main(int argc, char const *argv[]) {
      //opening the file
      FILE *fp = NULL;
      fp = fopen("tokens.txt","r");
      if (fp == NULL){
          fprintf(stderr, "File %s does not exist.\n");
          return 1;
      }
      // Generate postfix from file
      parse_file(fp);
    }

    //return str;
