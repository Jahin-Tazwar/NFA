#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "eval.h"

//helper function
Value number_to_value(int n) {
    Value value;
    value.is_function = 0;
    value.number = n;
    value.node = NULL;
    return value;
}

Value eval(ASTNode* node, SymbolTable* table) {
    if (!node) {
        printf("Error: NULL node in eval\n");
        return number_to_value(0);
    }

    if (node->type == AST_NUMBER) {
        return number_to_value(node->value);
    }

    if(node -> type == AST_VARIABLE) {
        return get_variable(table, node -> name);
    }

    if(node -> type == AST_ASSIGN) {
        Value value = eval(node -> right, table);

        set_variable(table, node -> name, value);

        return value;
    }

    if(node -> type == AST_FN) {
        Value value;

        value.is_function = 1;
        value.node = node;
        set_variable(table, node -> name, value);

        return value;
    }

    if(node -> type == AST_IF) {
        Value condition = eval(node -> left, table);
        
        if(condition.number) return eval(node -> right, table);
        else {
            if(node -> third != NULL) return eval(node -> third, table);
            else return number_to_value(0);
        }
    }

    if(node -> type == AST_COMPARISON_OP) {
        Value left_val = eval(node -> left, table);
        Value right_val = eval(node -> right, table);

        if(strcmp(node -> op, "==") == 0) {
            return number_to_value(left_val.number == right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, "!=") == 0) {
            return number_to_value(left_val.number != right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, "<") == 0) {
            return number_to_value(left_val.number < right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, ">") == 0) {
            return number_to_value(left_val.number > right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, "<=") == 0) {
            return number_to_value(left_val.number <= right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, ">=") == 0) {
            return number_to_value(left_val.number >= right_val.number ? 1 : 0);
        }

        printf("Error: unknown operator %s\n", node->op);
        return number_to_value(0);
    }

    if(node -> type == AST_LOGICAL_OP) {
        if(strcmp(node -> op, "!") == 0) {
            Value right_val = eval(node -> right, table);
            return number_to_value(right_val.number ? 0 : 1);
        }

        Value left_val = eval(node -> left, table);
        Value right_val = eval(node -> right, table);

        if(strcmp(node -> op, "&&") == 0) {
            return number_to_value(left_val.number && right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, "||") == 0) {
            return number_to_value(left_val.number || right_val.number ? 1 : 0);
        }

        printf("Error: unknown operator %s\n", node->op);
        return number_to_value(0);
    }

    if (node->type == AST_BINARY_OP) {
        Value left_val = eval(node->left, table);
        Value right_val = eval(node->right, table);

        if (strcmp(node -> op, "+") == 0) {
            return number_to_value(left_val.number + right_val.number);
        } 
        else if (strcmp(node -> op, "-") == 0) {
            return number_to_value(left_val.number - right_val.number);
        } 
        else if (strcmp(node -> op, "*") == 0) {
            return number_to_value(left_val.number * right_val.number);
        } 
        else if (strcmp(node -> op, "/") == 0) {
            if (right_val.number == 0) {
                printf("Error: division by zero\n");
                return number_to_value(0);
            }
            return number_to_value(left_val.number / right_val.number);
        }

        printf("Error: unknown operator %s\n", node->op);
        return number_to_value(0);
    }

    if(node -> type == AST_BLOCK) {
        Value result;

        for(int i = 0; i < node -> count; i++) {
            result = eval(node -> block[i], table);
        }

        return result;
    }

    printf("Error: unknown node type\n");
    return number_to_value(0);
}