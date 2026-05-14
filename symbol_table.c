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
    // For local table
    /* To avoid this, we start backwards --> i = table -> count - 1;
    > fn add(x, y) {let x = 10 let y = 13 x+y}
        <function: add>
        > let x = 20
        20
        > add (1, 1)
        2
    */
    for (int i = table -> count - 1; i >= 0; i--) { 
        if (strcmp(table->vars[i].name, name) == 0) {
            return table->vars[i].value;
        }
    }

    // If not found in local table
    if(table -> parent != NULL) {
        return get_variable(table -> parent, name);
    }

    printf("Error: undefined variable %s\n", name);
    Value err_val = {0, 0, NULL};
    return err_val;
}