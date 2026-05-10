#include <stdio.h>
#include "ast.h"

ASTNode* create_number(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node -> type = AST_NUMBER;
    node -> value = value;
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

ASTNode* create_binary_op(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node  = malloc(sizeof(ASTNode));
    node -> op = op;
    node -> left = left;
    node -> right = right;
    return node;
}