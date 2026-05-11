#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

ASTNode* create_number(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_NUMBER;
    node -> value = value;
    node -> left = NULL;
    node -> right = NULL;

    return node;
}

ASTNode* create_op(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_BINARY_OP;
    node -> op = op;
    node -> left = left;
    node -> right = right;

    return node;
}