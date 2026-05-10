#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUMBER,
    AST_BINARY_OP
} ASTNodeType;

typedef struct {
    ASTNodeType type;
    int value; //for numbers
    char op; // +, - etc.

    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode create_number(int value);
ASTNode create_binary_op(char op, ASTNode* left, ASTNode* right);

#endif // !AST_H