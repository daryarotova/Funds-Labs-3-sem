#include "../include/runner.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VARIABLES_COUNT 26

typedef struct {
    int variables[VARIABLES_COUNT];
    int initialized[VARIABLES_COUNT];
} VariableStore;

static void init_variable_store(VariableStore* store) {
    for (int i = 0; i < VARIABLES_COUNT; i++) {
        store->initialized[i] = 0;
        store->variables[i] = 0;
    }
}

static int get_variable_index(char name) {
    if (name >= 'A' && name <= 'Z') {
        return name - 'A';
    }
    return -1;
}

static ParseStatus evaluate_rpn(TokenList* rpn, VariableStore* store, int* result) {
    if (!rpn || !store || !result) return PARSE_EVAL_ERROR;
    
    TokenList stack = list_create();
    ListNode* current = rpn->head;
    
    while (current) {
        TokenItem token = current->item;
        
        switch (token.type) {
            case TOKEN_NUMBER:
                stack_push(&stack, token);
                break;
                
            case TOKEN_NAME: {
                int var_index = get_variable_index(token.value.chr);
                if (var_index == -1 || !store->initialized[var_index]) {
                    list_clear(&stack);
                    return PARSE_EVAL_ERROR;
                }
                TokenItem num_token = {TOKEN_NUMBER, {.num = store->variables[var_index]}};
                stack_push(&stack, num_token);
                break;
            }
                
            case TOKEN_OPERATOR: {
                if (stack.size < 2) {
                    list_clear(&stack);
                    return PARSE_EVAL_ERROR;
                }
                
                TokenItem right = stack_pop(&stack);
                TokenItem left = stack_pop(&stack);
                
                if (left.type != TOKEN_NUMBER || right.type != TOKEN_NUMBER) {
                    list_clear(&stack);
                    return PARSE_EVAL_ERROR;
                }
                
                int left_val = left.value.num;
                int right_val = right.value.num;
                int result_val;
                
                switch (token.value.chr) {
                    case '+': result_val = left_val + right_val; break;
                    case '-': result_val = left_val - right_val; break;
                    case '*': result_val = left_val * right_val; break;
                    case '/': 
                        if (right_val == 0) {
                            list_clear(&stack);
                            return PARSE_EVAL_ERROR;
                        }
                        result_val = left_val / right_val; 
                        break;
                    case '^': result_val = int_power(left_val, right_val); break;
                    default:
                        list_clear(&stack);
                        return PARSE_EVAL_ERROR;
                }
                
                TokenItem result_token = {TOKEN_NUMBER, {.num = result_val}};
                stack_push(&stack, result_token);
                break;
            }
                
            case TOKEN_UNARY_OPERATOR: {
                if (stack.size < 1) {
                    list_clear(&stack);
                    return PARSE_EVAL_ERROR;
                }
                
                TokenItem operand = stack_pop(&stack);
                if (operand.type != TOKEN_NUMBER) {
                    list_clear(&stack);
                    return PARSE_EVAL_ERROR;
                }
                
                int result_val;
                switch (token.value.chr) {
                    case '~':
                        result_val = -operand.value.num;
                        break;
                    case '#':
                        result_val = operand.value.num;
                        break;
                    default:
                        list_clear(&stack);
                        return PARSE_EVAL_ERROR;
                }
                
                TokenItem result_token = {TOKEN_NUMBER, {.num = result_val}};
                stack_push(&stack, result_token);
                break;
            }
                
            default:
                list_clear(&stack);
                return PARSE_EVAL_ERROR;
        }
        
        current = current->next;
    }
    
    if (stack.size != 1) {
        list_clear(&stack);
        return PARSE_EVAL_ERROR;
    }
    
    TokenItem final_result = stack_pop(&stack);
    if (final_result.type != TOKEN_NUMBER) {
        list_clear(&stack);
        return PARSE_EVAL_ERROR;
    }
    
    *result = final_result.value.num;
    list_clear(&stack);
    return PARSE_OK;
}

static ParseStatus parse_line(const char* line, TokenList* tokens) {
    if (!line || !tokens) return PARSE_INVALID_EXPRESSION;
    
    const char* ptr = line;
    
    while (*ptr) {
        if (isspace(*ptr)) {
            ptr++;
            continue;
        }
        
        TokenItem token = {TOKEN_NONE, {0}};
        
        if (isdigit(*ptr)) {
            char* end;
            int value = strtol(ptr, &end, 10);
            if (end == ptr) {
                return PARSE_TOKEN_ERROR;
            }
            
            token.type = TOKEN_NUMBER;
            token.value.num = value;
            ptr = end;
        }
        else if (*ptr >= 'A' && *ptr <= 'Z') {
            token.type = TOKEN_NAME;
            token.value.chr = *ptr;
            ptr++;
        }
        else if (is_operator(*ptr)) {
            token.type = TOKEN_OPERATOR;
            token.value.chr = *ptr;
            ptr++;
        }
        else if (*ptr == '(') {
            token.type = TOKEN_LEFT_PAREN;
            token.value.chr = *ptr;
            ptr++;
        }
        else if (*ptr == ')') {
            token.type = TOKEN_RIGHT_PAREN;
            token.value.chr = *ptr;
            ptr++;
        }
        else {
            return PARSE_TOKEN_ERROR;
        }
        
        queue_enqueue(tokens, token);
    }
    
    return PARSE_OK;
}

static void write_log_entry(FILE* log, int line_num, const char* command, VariableStore* store, const char* operation) {
    if (!log || !command || !store || !operation) return;
    
    fprintf(log, "[%d] %s | ", line_num, command);
    
    int first = 1;
    for (int i = 0; i < VARIABLES_COUNT; i++) {
        if (store->initialized[i]) {
            if (!first) {
                fprintf(log, ", ");
            }
            fprintf(log, "%c=%d", 'A' + i, store->variables[i]);
            first = 0;
        }
    }
    
    fprintf(log, " | %s\n", operation);
}

ParseStatus process_input(FILE* source, FILE* log_output) {
    if (!source || !log_output) return PARSE_INVALID_EXPRESSION;
    
    VariableStore store;
    init_variable_store(&store);
    
    char line[256];
    int line_num = 0;
    
    while (fgets(line, sizeof(line), source)) {
        line_num++;
        char* newline = strchr(line, '\n');
        if (newline) *newline = '\0';
        
        char original_line[256];
        strcpy(original_line, line);
        normalize_string(line);
        if (strlen(line) == 0) continue;
        
        CommandType cmd_type;
        detect_command(line, &cmd_type);
        
        if (cmd_type == CMD_SET) {
            char* equals = strchr(line, '=');
            if (!equals) {
                write_log_entry(log_output, line_num, original_line, &store, "Invalid assignment");
                continue;
            }
            
            *equals = '\0';
            char* var_name_str = line;
            char* expression = equals + 1;
            
            normalize_string(var_name_str);
            normalize_string(expression);
            
            if (strlen(var_name_str) != 1 || !isupper(var_name_str[0])) {
                write_log_entry(log_output, line_num, original_line, &store, "Invalid variable name");
                continue;
            }
            
            char var_name = var_name_str[0];
            int var_index = get_variable_index(var_name);
            
            TokenList tokens = list_create();
            ParseStatus status = parse_line(expression, &tokens);
            
            if (status == PARSE_OK) {
                TokenList rpn = list_create();
                status = convert_to_rpn(&tokens, &rpn);
                
                if (status == PARSE_OK) {
                    int result;
                    status = evaluate_rpn(&rpn, &store, &result);
                    
                    if (status == PARSE_OK) {
                        store.variables[var_index] = result;
                        store.initialized[var_index] = 1;
                        write_log_entry(log_output, line_num, original_line, &store, "Assignment");
                    }
                }
                
                list_clear(&rpn);
            }
            
            if (status != PARSE_OK) {
                write_log_entry(log_output, line_num, original_line, &store, "Evaluation error");
            }
            
            list_clear(&tokens);
        }
        else if (cmd_type == CMD_PRINT) {
            if (strlen(line) < 7 || strncmp(line, "print(", 6) != 0 || line[strlen(line)-1] != ')') {
                write_log_entry(log_output, line_num, original_line, &store, "Invalid print syntax");
                continue;
            }
            
            char expression[256];
            strncpy(expression, line + 6, strlen(line) - 7);
            expression[strlen(line) - 7] = '\0';
            normalize_string(expression);
            TokenList tokens = list_create();
            ParseStatus status = parse_line(expression, &tokens);
            
            if (status == PARSE_OK) {
                TokenList rpn = list_create();
                status = convert_to_rpn(&tokens, &rpn);
                
                if (status == PARSE_OK) {
                    int result;
                    status = evaluate_rpn(&rpn, &store, &result);
                    
                    if (status == PARSE_OK) {
                        printf("%d\n", result);
                        write_log_entry(log_output, line_num, original_line, &store, "Print");
                    }
                }
                
                list_clear(&rpn);
            }
            
            if (status != PARSE_OK) {
                write_log_entry(log_output, line_num, original_line, &store, "Print evaluation error");
            }
            
            list_clear(&tokens);
        }
        else {
            write_log_entry(log_output, line_num, original_line, &store, "Invalid command");
        }
    }
    
    return PARSE_OK;
}

void run_program(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return;
    }
    
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Error: Cannot open input file %s\n", argv[1]);
        return;
    }
    
    FILE* log_file = fopen("trace.log", "w");
    if (!log_file) {
        printf("Error: Cannot create log file\n");
        fclose(input_file);
        return;
    }
    
    ParseStatus status = process_input(input_file, log_file);
    
    fclose(input_file);
    fclose(log_file);
    
    if (status != PARSE_OK) {
        printf("Program completed with errors: check trace.log\n");
    } else {
        printf("Program completed successfully: see trace.log\n");
    }
}