#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"

typedef struct {
    int is_function;
    int number;
    struct ASTNode* node;
} Value;

typedef struct {
    char name[64];
    Value value;
} Variable;

#define MAX_VARS 100

typedef struct {
    Variable vars[MAX_VARS];
    int count;
} SymbolTable;


void set_variable(SymbolTable* table, char name[], Value value);
Value get_variable(SymbolTable* table, char name[]);

#endif // !SYMBOL_H