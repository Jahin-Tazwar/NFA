#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    AST_NUMBER,
    AST_BINARY_OP, // + - * /
    AST_VARIABLE,
    AST_ASSIGN,
    AST_COMPARISON_OP, // == != < > <= >=
    AST_LOGICAL_OP // && || !
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char name[64];
    char op[8]; // For binary operators and comparison operators
    int value; // only for numbers
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* create_number(int value);
ASTNode* create_op(char op[], ASTNode* left, ASTNode* right);
ASTNode* create_variable(char name[]);
ASTNode* create_assignment(char name[], ASTNode* value);
#endif