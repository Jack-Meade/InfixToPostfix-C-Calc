typedef struct __token {
    char type;
    int value;
} token;

void printToken(token *t) {
    // -> tells pointer to access this part
    printf("Token type=%c, value=%d\n", t->type, t->value);
}

token *create_token(char type, char *value) {
    // Local var are allocated on stack, and will be deallocated when function call ended.
    // You can allocate memory on the heap so this memory space for the var will stay forever.
    // Make token, cast by allocating memory (malloc) to the size of token data type (needs to know how much memory to allocate).
    token *t = (token *)malloc(sizeof(token));
    t->type = type;
    t->value = *value;
    return t;
}
