#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "list.h"
#include "tokens.h"

typedef enum {
    EXPECT_VALUE,
    EXPECT_OPERATOR
} ParseMode;

typedef enum {
    ASSOC_LEFT,
    ASSOC_RIGHT
} AssocRule;

ParseStatus convert_to_rpn(TokenList* input, TokenList* output);

#endif
