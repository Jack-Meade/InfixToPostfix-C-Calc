// CS3500 Project - Token
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <string.h>

typedef struct __token {
    char type;          // Type: int, float, operator
    char *value;        // Value: of type
} token;

// Prints Token contents
void print_token(token *t) {
    printf("Token type=%c, value=%s\n", t->type, t->value);
}

// Creates and returns Token struct
token *create_token(char type, char *value) {
    token *t = (token *)malloc(sizeof(token));  // Token size is variable
    t->type = type;                             // Type indicated by single char
    t->value = malloc(strlen(value)+1);         // Value size is length on string+1 for NULL char
    strcpy(t->value, value);                    // Have to copy otherwise Token value is tied to original string
    return t;
}
