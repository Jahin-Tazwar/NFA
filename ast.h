#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    AST_NUMBER,
    AST_BINARY_OP
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char op; // '+', '-', '*' ... or 0 for number
    int value; // only for numbers

    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* create_number(int value);
ASTNode* create_op(char op, ASTNode* left, ASTNode* right);
ASTNode* parse_simple_expression(Lexer* lexer);

#endif