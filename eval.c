#include "stdio.h"
#include "stdlib.h"
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

    if(node -> type == AST_ASSIGN) {
        return get_variable(table, node -> name);
    }

    if (node->type == AST_BINARY_OP) {
        int left_val = eval(node->left, table);
        int right_val = eval(node->right, table);

        if (node->op == '+') {
            return left_val + right_val;
        } 
        else if (node->op == '-') {
            return left_val - right_val;
        } 
        else if (node->op == '*') {
            return left_val * right_val;
        } 
        else if (node->op == '/') {
            if (right_val == 0) {
                printf("Error: division by zero\n");
                return 0;
            }
            return left_val / right_val;
        }

        printf("Error: unknown operator %c\n", node->op);
        return 0;
    }

    printf("Error: unknown node type\n");
    return 0;
}