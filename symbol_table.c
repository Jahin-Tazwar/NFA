#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "symbol_table.h"

void set_variable(SymbolTable* table, char name[], Value value) {
    // First, check if it already exists and update it!
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->vars[i].name, name) == 0) {
            table->vars[i].value = value;
            return;
        }
    }

    // Only if it's new, add it to the end
    if (table->count >= MAX_VARS) {
        printf("Error: Symbol Table Full!\n");
        return;
    }

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

    //{is_void, is_function, number, node, is_builtin, builtin_ptr}
    // Value err_val = {1, 0, 0, NULL, 0, NULL};
    // return err_val;

    printf("Error: undefined variable '%s'\n", name);
    exit(1); // crash program.
}

void update_variable(SymbolTable* table, char name[], Value value) {
    //Check the local table
    for(int i = 0; i < table -> count; i++) {
        if(strcmp(table -> vars[i].name, name) == 0) {
            table -> vars[i].value = value;
            return;
        }
    }

    //Check the parent table
    if(table -> parent != NULL) {
        update_variable(table -> parent, name, value);
        return;
    }
    

    printf("Error: cannot update undefined variable '%s'\n", name);
    exit(1);
}