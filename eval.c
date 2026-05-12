#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "symbol_table.h"
#include "eval.h"

int eval(ASTNode* node, SymbolTable* table) {
    if (!node) {
        printf("Error: NULL node in eval\n");
        return 0;
    }

    if (node->type == AST_NUMBER) {
        return node->value;
    }

    if(node -> type == AST_VARIABLE) {
        return get_variable(table, node -> name);
    }

    if(node -> type == AST_ASSIGN) {
        int value = eval(node -> right, table);

        set_variable(table, node -> name, value);

        return value;
    }

    if(node -> type == AST_COMPARISON_OP) {
        int left_val = eval(node -> left, table);
        int right_val = eval(node -> right, table);

        if(strcmp(node -> op, "==") == 0) {
            return left_val == right_val ? 1 : 0;
        }else if(strcmp(node -> op, "!=") == 0) {
            return left_val != right_val ? 1 : 0;
        }else if(strcmp(node -> op, "<") == 0) {
            return left_val < right_val ? 1 : 0;
        }else if(strcmp(node -> op, ">") == 0) {
            return left_val > right_val ? 1 : 0;
        }else if(strcmp(node -> op, "<=") == 0) {
            return left_val <= right_val ? 1 : 0;
        }else if(strcmp(node -> op, ">=") == 0) {
            return left_val >= right_val ? 1 : 0;
        }

        printf("Error: unknown operator %s\n", node->op);
        return 0;
    }

    if(node -> type == AST_LOGICAL_OP) {
        if(strcmp(node -> op, "!") == 0) {
            int right_val = eval(node -> right, table);
            return right_val ? 0 : 1;
        }

        int left_val = eval(node -> left, table);
        int right_val = eval(node -> right, table);

        if(strcmp(node -> op, "&&") == 0) {
            return left_val && right_val ? 1 : 0;
        }else if(strcmp(node -> op, "||") == 0) {
            return left_val || right_val ? 1 : 0;
        }

        printf("Error: unknown operator %s\n", node->op);
        return 0;
    }

    if (node->type == AST_BINARY_OP) {
        int left_val = eval(node->left, table);
        int right_val = eval(node->right, table);

        if (strcmp(node -> op, "+") == 0) {
            return left_val + right_val;
        } 
        else if (strcmp(node -> op, "-") == 0) {
            return left_val - right_val;
        } 
        else if (strcmp(node -> op, "*") == 0) {
            return left_val * right_val;
        } 
        else if (strcmp(node -> op, "/") == 0) {
            if (right_val == 0) {
                printf("Error: division by zero\n");
                return 0;
            }
            return left_val / right_val;
        }

        printf("Error: unknown operator %s\n", node->op);
        return 0;
    }

    printf("Error: unknown node type\n");
    return 0;
}