#ifndef SYMBOL_H
#define SYMBOL_H

#include "ast.h"


typedef enum {
    VAL_VOID,
    VAL_NUMBER,
    VAL_STRING,
    VAL_ARRAY,
    VAL_BOOL,
    VAL_FUNCTION,
    VAL_BUILTIN
} ValueType;

struct Value; 

typedef struct Value {
    ValueType type;

    union {
        int number;
        int boolean;
        char* string_value;
        //For arrays
        struct {
            struct Value* elements;
            int count;
        } array;

        struct {
            struct ASTNode* node;
        } function;

        struct Value (*builtin)(struct Value* args, int arg_count);
    } as;
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