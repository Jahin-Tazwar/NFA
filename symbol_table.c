#include "stdio.h"
#include "string.h"
#include "symbol_table.h"

void set_variable(SymbolTable* table, char name[], Value value) {
    Variable var;

    strcpy(var.name, name);

    var.value = value;

    table->vars[table->count] = var;
    table->count++;
}

Value get_variable(SymbolTable* table, char name[]) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->vars[i].name, name) == 0) {
            return table->vars[i].value;
        }
    }

    printf("Error: undefined variable %s\n", name);
    Value err_val = {0, 0, NULL};
    return err_val;
}