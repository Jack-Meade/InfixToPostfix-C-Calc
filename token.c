// CS3500 Project - Token
// Conor Patrick Mc Donald, Daniels Leonards Bindemans, Jack Meade

#include <string.h>

// Defines Token struct
typedef struct __token {
    char type;                                  // Type: (i)nt, (f)loat, (o)perator
    char *value;                                // Value: string representing value of type
} token;

// Prints Token contents
void print_token(token *t) {
    printf("Token type=%c, value=%s\n", t->type, t->value);
}

// Creates and returns Token struct
token *create_token(char type, char *value) {
    token *t = (token *)malloc(sizeof(token));  // Token size is variable
    t->type = type;                             // Type indicated by single char
    t->value = malloc(strlen(value));           // Value size is length on string
    strcpy(t->value, value);                    // Have to copy otherwise Token value is tied to original string
    return t;
}
