#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    AST_NUMBER,
    AST_VARIABLE,
    AST_ASSIGN,

    AST_IF,

    AST_FN,
    AST_CALL,
    
    AST_BINARY_OP, // + - * /
    AST_COMPARISON_OP, // == != < > <= >=
    AST_LOGICAL_OP, // && || !

    AST_BLOCK // holds blocks of code
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char name[64];
    char op[8]; // For binary operators and comparison operators
    int value; // only for numbers

    char params[16][64]; // Function parameters
    int param_count;

    struct ASTNode* args[16]; // Up to 16 arguments
    int arg_count;

    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* third; // used for false branch

    struct ASTNode* block[64]; // holds blocks of code
    int count; // keeps count of statements.
} ASTNode;

ASTNode* create_number(int value);
ASTNode* create_op(char op[], ASTNode* left, ASTNode* right);
ASTNode* create_variable(char name[]);
ASTNode* create_assignment(char name[], ASTNode* value);
ASTNode* create_if(ASTNode* condition, ASTNode* true_branch, ASTNode* false_branch);
ASTNode* create_block(ASTNode* block[], int count);
ASTNode* create_function(char name[], char params[][64], int param_count, ASTNode* body);
ASTNode* create_call(char name[], ASTNode* args[], int arg_count);

#endif