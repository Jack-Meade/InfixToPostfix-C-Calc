#include <string.h>

typedef struct __token {
    char type;
    char *value;
} token;

void printToken(token *t) {
    printf("Token type=%c, value=%s\n", t->type, t->value);
}

token *create_token(char type, char *value) {
    token *t = (token *)malloc(sizeof(token));
    t->type = type;
    t->value = malloc(strlen(value)+1);
    t->value = value;
    return t;
}
