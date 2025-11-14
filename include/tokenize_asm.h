#ifndef TOKENIZE_ASM_H
#define TOKENIZE_ASM_H

typedef enum {
    REGISTER,
    INT_LITERAL,
    ADDRESS,
    DIRECTIVE,
    INSTRUCTION,
    LABEL,
    COMMENT,
    EXCLUDE
} TOKEN_TYPE;

typedef struct {
    TOKEN_TYPE type;
    char* value;
} Token;

Token* tokenize(char* contents);


#endif