#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "ast.h"

ASTNode* create_number(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_NUMBER;
    node -> value = value;
    node -> left = NULL;
    node -> right = NULL;

    return node;
}

ASTNode* create_op(char op[], ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    
    if (strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 || strcmp(op, "<") == 0 || strcmp(op, ">") == 0 || strcmp(op, "<=") == 0 || strcmp(op, ">=") == 0) {
        node -> type = AST_COMPARISON_OP;
    } else if (strcmp(op, "&&") == 0 || strcmp(op, "||") == 0 || strcmp(op, "!") == 0) {
        node -> type = AST_LOGICAL_OP;
    } else {
        node -> type = AST_BINARY_OP;
    }
    
    strcpy(node -> op, op);
    node -> left = left;
    node -> right = right;

    return node;
}

ASTNode* create_if(ASTNode* condition, ASTNode* true_branch, ASTNode* false_branch) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_IF;
    strcpy(node -> op, "if");
    node -> left = condition;
    node -> right = true_branch;
    node -> third = false_branch;

    return node;
}

ASTNode* create_variable(char name[]) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_VARIABLE;
    strcpy(node -> name, name);

    return node;
}

ASTNode* create_assignment(char name[], ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_ASSIGN;
    strcpy(node -> name, name);

    node -> right = value;
    node -> left = NULL;

    return node;
}

ASTNode* create_block(ASTNode* block[], int count) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_BLOCK;
    node -> count = count;
    
    for(int i = 0; i < count; i++) {
        node -> block[i] = block[i];
    }

    return node;
}

ASTNode* create_function(char name[], char params[][64], int param_count, ASTNode* body){
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_FN;
    strcpy(node -> name, name);
    node -> param_count = param_count;

    for(int i = 0; i < param_count; i++) {
        strcpy(node -> params[i], params[i]);
    }

    node -> right = body;

    return node;
}

ASTNode* create_call(char name[], ASTNode* args[], int arg_count) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_CALL;
    strcpy(node -> name, name);
    node -> arg_count = arg_count;

    for(int i = 0; i < arg_count; i++) {
        node -> args[i] = args[i];
    }

    return node;
}

ASTNode* create_while(ASTNode* condition, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_WHILE;
    node -> left = condition;
    node -> right = body;

    return node;
}

//Updates vars
ASTNode* create_update(char name[], ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));

    node -> type = AST_UPDATE;
    strcpy(node -> name, name);

    node -> right = value;
    node -> left = NULL;

    return node;
}