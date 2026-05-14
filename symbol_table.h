#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"


struct Value; 

typedef struct Value {
    int is_void;

    int is_function;
    int number;
    struct ASTNode* node;

    int is_builtin;
    struct Value (*builtin)(struct Value* args, int arg_count);
} Value;


typedef struct {
    char name[64];
    Value value;
} Variable;

#define MAX_VARS 100

typedef struct SymbolTable {
    int count;
    Variable vars[MAX_VARS];
    struct SymbolTable* parent;
} SymbolTable;


void set_variable(SymbolTable* table, char name[], Value value);
Value get_variable(SymbolTable* table, char name[]);
void update_variable(SymbolTable* table, char name[], Value value);

#endif // !SYMBOL_H