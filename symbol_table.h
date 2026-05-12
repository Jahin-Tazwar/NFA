#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct {
    char name[64];
    int value;
} Variable;

#define MAX_VARS 100

typedef struct {
    Variable vars[MAX_VARS];
    int count;
} SymbolTable;


void set_variable(SymbolTable* table, char* name, int value);
int get_variable(SymbolTable* table, char* name);

#endif // !SYMBOL_H