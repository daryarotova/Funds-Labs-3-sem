#include "../include/parser.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int get_operator_precedence(char op) {
    switch (op) {
        case '=': return 1;
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        case '^': return 4;
        case '~': return 5;
        default: return 0;
    }
}

static AssocRule get_operator_associativity(char op) {
    switch (op) {
        case '^': case '~': return ASSOC_RIGHT;
        default: return ASSOC_LEFT;
    }
}

static bool is_unary_operator(char op, ParseMode mode) {
    return (op == '-' || op == '+') && mode == EXPECT_VALUE;
}

ParseStatus convert_to_rpn(TokenList* input, TokenList* output) {
    if (!input || !output) return PARSE_INVALID_EXPRESSION;
    
    TokenList stack = list_create();
    ParseMode mode = EXPECT_VALUE;
    
    ListNode* current = input->head;
    while (current) {
        TokenItem token = current->item;
        
        switch (token.type) {
            case TOKEN_NUMBER:
            case TOKEN_NAME:
                if (mode != EXPECT_VALUE) {
                    list_clear(&stack);
                    return PARSE_INVALID_EXPRESSION;
                }
                queue_enqueue(output, token);
                mode = EXPECT_OPERATOR;
                break;
                
            case TOKEN_OPERATOR:
                if (mode == EXPECT_VALUE && is_unary_operator(token.value.chr, mode)) {
                    TokenItem unary_token = token;
                    unary_token.type = TOKEN_UNARY_OPERATOR;
                    unary_token.value.chr = (token.value.chr == '-') ? '~' : '#'; // '~' - унарный минус, '#' - унарный плюс
                    stack_push(&stack, unary_token);
                } else if (mode == EXPECT_OPERATOR) {
                    while (stack.head) {
                        TokenItem top = stack_top(&stack);
                        if (top.type != TOKEN_OPERATOR && top.type != TOKEN_UNARY_OPERATOR) break;
                        
                        int current_prec = get_operator_precedence(token.value.chr);
                        int top_prec = get_operator_precedence(top.value.chr);
                        AssocRule current_assoc = get_operator_associativity(token.value.chr);
                        
                        if ((current_assoc == ASSOC_LEFT && current_prec <= top_prec) ||
                            (current_assoc == ASSOC_RIGHT && current_prec < top_prec)) {
                            queue_enqueue(output, stack_pop(&stack));
                        } else {
                            break;
                        }
                    }
                    
                    stack_push(&stack, token);
                    mode = EXPECT_VALUE;
                } else {
                    list_clear(&stack);
                    return PARSE_INVALID_EXPRESSION;
                }
                break;
                
            case TOKEN_LEFT_PAREN:
                if (mode != EXPECT_VALUE) {
                    list_clear(&stack);
                    return PARSE_INVALID_EXPRESSION;
                }
                stack_push(&stack, token);
                break;
                
            case TOKEN_RIGHT_PAREN:
                if (mode != EXPECT_OPERATOR) {
                    list_clear(&stack);
                    return PARSE_INVALID_EXPRESSION;
                }
                
                bool found_left_paren = false;
                while (stack.head) {
                    TokenItem top = stack_pop(&stack);
                    if (top.type == TOKEN_LEFT_PAREN) {
                        found_left_paren = true;
                        break;
                    }
                    queue_enqueue(output, top);
                }
                
                if (!found_left_paren) {
                    list_clear(&stack);
                    return PARSE_INVALID_EXPRESSION;
                }
                break;
                
            default:
                list_clear(&stack);
                return PARSE_TOKEN_ERROR;
        }
        
        current = current->next;
    }
    
    while (stack.head) {
        TokenItem top = stack_pop(&stack);
        if (top.type == TOKEN_LEFT_PAREN) {
            list_clear(&stack);
            return PARSE_INVALID_EXPRESSION;
        }
        queue_enqueue(output, top);
    }
    
    list_clear(&stack);
    return PARSE_OK;
}