// CS3500 Project - token
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Defines token struct
typedef struct __token {
    char type;                                  // Type: (i)nt, (f)loat, (o)perator
    char *value;                                // Value: string representing value of type
} token;

// Creates and returns token struct
token *create_token(char type, char *value) {
    token *t = (token *)malloc(sizeof(token));  // token size is variable
    t->type = type;                             // Type indicated by single char
    t->value = malloc(strlen(value));           // Value size is length on string
    strcpy(t->value, value);                    // Have to copy otherwise token value is tied to original string
    return t;
}

// Prints token contents
void print_token(token *t) {
    printf("token type=%c, value=%s\n", t->type, t->value);
}

// Prints array of tokens
void print_token_array(token *tokens) {
    int tp = -1;

    // Print tokens until reached end token with value of NULL
    while (tokens[++tp].value) {
        print_token(&tokens[tp]);
    }
}
