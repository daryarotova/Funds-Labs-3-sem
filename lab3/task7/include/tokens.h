#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    TOKEN_NONE,
    TOKEN_NUMBER,
    TOKEN_NAME,
    TOKEN_OPERATOR,
    TOKEN_UNARY_OPERATOR,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN
} TokenType;

typedef union {
    int num;
    char chr;
} TokenValue;

typedef struct {
    TokenType type;
    TokenValue value;
} TokenItem;

typedef enum {
    PARSE_OK,
    PARSE_INVALID_EXPRESSION,
    PARSE_TOKEN_ERROR,
    PARSE_EVAL_ERROR
} ParseStatus;

#endif