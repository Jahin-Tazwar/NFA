#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "eval.h"

//helper function
Value void_value() {
    Value v;
    v.is_void = 1;
    v.is_function = 0;
    v.is_builtin = 0;
    v.is_string = 0;
    v.is_array = 0;
    v.array_elements = NULL;
    v.array_count = 0;
    v.string_value = NULL;
    v.number = 0;
    return v;
}

Value number_to_value(int n) {
    Value value;
    value.is_void = 0;
    value.is_function = 0;
    value.is_builtin = 0;
    value.number = n;
    value.is_string = 0;
    value.string_value = NULL;
    value.is_array = 0;
    value.array_elements = NULL;
    value.array_count = 0;
    value.node = NULL;
    return value;
}

static void print_value_rec(Value val, int quote_strings) {
    if (val.is_array) {
        printf("[");
        for (int j = 0; j < val.array_count; j++) {
            // Recursion! Call ourselves to print this element
            print_value_rec(val.array_elements[j], 1);
            
            if (j < val.array_count - 1) {
                printf(", ");
            }
        }
        printf("]");
    } else if (val.is_string) {
        if (quote_strings) {
            printf("\"%s\"", val.string_value); // Quote strings inside arrays
        } else {
            printf("%s", val.string_value);       // Plain print for top-level strings
        }
    } else if (val.is_function) {
        printf("<function>");
    } else if (val.is_void) {
        // Do nothing
    } else {
        printf("%d", val.number);
    }
}


Value builtin_print(Value args[], int arg_count) {
    for(int i = 0; i < arg_count; i++) {
        print_value_rec(args[i], 0);

        if(i < arg_count - 1) {
            printf(" ");
        }
    }
    printf("\n");
    return void_value();
}

Value builtin_len(Value args[], int arg_count) {
    Value length = void_value();
    length.is_void = 0;

    if(arg_count != 1) {
        printf("Error: too many arguments. Expected 1");
        exit(1);
    }

    if(args[0].is_array) {
        length.number = args[0].array_count;
        return length;
    }else if(args[0].is_string) {
        length.number = strlen(args[0].string_value);
        return length;
    }

    printf("Error: Unexpected argument type. Expected array or string");
    exit(1);
}

void setup_builtins(SymbolTable* table) {
    Value print_val;
    print_val.is_function = 0;
    print_val.is_builtin = 1;
    print_val.builtin = builtin_print;

    Value len_val = void_value();
    len_val.is_void = 0;
    len_val.is_builtin = 1;
    len_val.builtin = builtin_len;

    set_variable(table, "print", print_val);
    set_variable(table, "len", len_val);
}

Value eval(ASTNode* node, SymbolTable* table) {
    if (!node) {
        printf("Error: NULL node in eval\n");
        return number_to_value(0);
    }

    if (node->type == AST_NUMBER) {
        return number_to_value(node->value);
    }

    if(node -> type == AST_STRING) {
        Value value = void_value();
        value.is_void = 0;
        value.is_string = 1;

        value.string_value = strdup(node -> string_value);
        return value;
    }

    if(node -> type == AST_ARRAY) {
        Value value = void_value();
        value.is_void = 0;
        value.is_array = 1;
        value.array_count = node -> array_count;

        value.array_elements = malloc(node -> array_count * sizeof(Value));

        for(int i = 0; i < node -> array_count; i++) {
            value.array_elements[i] = eval(node -> array_elements[i], table);
        }

        return value;
    }

    if(node -> type == AST_INDEX) {
        Value arr = eval(node -> left, table);
        Value idx = eval(node -> right, table);

        if(!arr.is_array) {
            printf("Error: Cannot index a non-array value\n");
            exit(1);
        }

        if(idx.is_string || idx.is_array) {
            printf("Error: Array index must be a number\n");
            exit(1);
        }

        if(idx.number < 0 || idx.number >= arr.array_count) {
            printf("Error: Index out of bounds!\n");
            exit(1);
        }

        return arr.array_elements[idx.number];
    }


    if(node -> type == AST_VARIABLE) {
        return get_variable(table, node -> name);
    }

    if(node -> type == AST_ASSIGN) {
        Value value = eval(node -> right, table);

        set_variable(table, node -> name, value);

        return void_value();
    }

    if(node -> type == AST_UPDATE) {
        Value value = eval(node -> right, table);
        
        update_variable(table, node -> name, value);

        return void_value();
    }

    // arr[idx] = value
    if(node -> type == AST_INDEX_UPDATE) {
        Value arr = eval(node -> left, table);
        Value idx = eval(node -> right, table);
        Value updated_value = eval(node -> third, table);

        if(!arr.is_array) {
            printf("Error: Cannot assign to non-array element\n");
            exit(1);
        }
        if(idx.is_string || idx.is_array) {
            printf("Error: Array index must be a number\n");
            exit(1);
        }
        if(idx.number < 0 || idx.number >= arr.array_count) {
            printf("Error: Index out of bounds!\n");
            exit(1);
        }

        arr.array_elements[idx.number] = updated_value;

        return void_value();
    }

    if(node -> type == AST_WHILE) {
        SymbolTable* local_table = malloc(sizeof(SymbolTable));
        local_table -> parent = table;
        
        while(eval(node -> left, table).number != 0) {
            local_table -> count = 0; // wipes while blocks data after every iteration
            eval(node -> right, local_table);
        }

        //clean up the ram when the loop is done
        free(local_table);
        return void_value();
    }

    if(node -> type == AST_FN) {
        Value value;

        value.is_function = 1;
        value.node = node;
        set_variable(table, node -> name, value);

        return void_value();
    }

    if(node -> type == AST_CALL) {
        Value func = get_variable(table, node -> name);

        // Dynamically allocate to avoid stack frame bloat in WASM
        Value* arg_values = malloc(16 * sizeof(Value));
        for(int i = 0; i < node -> arg_count; i++) {
            arg_values[i] = eval(node -> args[i], table);
        }

        if(func.is_function) {
            // malloc for moving the table to the Heap (avoiding WASM stack overflow)
            SymbolTable* local_table = malloc(sizeof(SymbolTable));
            local_table->count = 0;
            local_table->parent = table;

            ASTNode* func_node = func.node;

            for(int i = 0; i < func_node -> param_count; i++) {
                set_variable(local_table, func_node -> params[i], arg_values[i]);
            }

            Value res = eval(func_node -> right, local_table);
            
            free(local_table); // Clean up the memory!
            free(arg_values);  // Free heap array!
            return res;
        }else if(func.is_builtin){
            Value res = func.builtin(arg_values, node -> arg_count);
            free(arg_values);  // Free heap array!
            return res;
        } else {
            printf("Error: %s is not a function\n", node->name);
            free(arg_values);  // Free heap array!
            return number_to_value(0);
        }
    }


    if(node -> type == AST_IF) {
        Value condition = eval(node -> left, table);
        
        if(condition.number) return eval(node -> right, table);
        else {
            if(node -> third != NULL) return eval(node -> third, table);
            else return number_to_value(0);
        }
    }

    if(node -> type == AST_COMPARISON_OP) {
        Value left_val = eval(node -> left, table);
        Value right_val = eval(node -> right, table);

        if(strcmp(node -> op, "==") == 0) {
            return number_to_value(left_val.number == right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, "!=") == 0) {
            return number_to_value(left_val.number != right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, "<") == 0) {
            return number_to_value(left_val.number < right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, ">") == 0) {
            return number_to_value(left_val.number > right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, "<=") == 0) {
            return number_to_value(left_val.number <= right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, ">=") == 0) {
            return number_to_value(left_val.number >= right_val.number ? 1 : 0);
        }

        printf("Error: unknown operator %s\n", node->op);
        return number_to_value(0);
    }

    if(node -> type == AST_LOGICAL_OP) {
        if(strcmp(node -> op, "!") == 0) {
            Value right_val = eval(node -> right, table);
            return number_to_value(right_val.number ? 0 : 1);
        }

        Value left_val = eval(node -> left, table);
        Value right_val = eval(node -> right, table);

        if(strcmp(node -> op, "&&") == 0) {
            return number_to_value(left_val.number && right_val.number ? 1 : 0);
        }else if(strcmp(node -> op, "||") == 0) {
            return number_to_value(left_val.number || right_val.number ? 1 : 0);
        }

        printf("Error: unknown operator %s\n", node->op);
        return number_to_value(0);
    }

    if (node->type == AST_BINARY_OP) {
        Value left_val = eval(node->left, table);
        Value right_val = eval(node->right, table);

        if (strcmp(node -> op, "+") == 0) {

            //For string concat
            if(left_val.is_string && right_val.is_string) {
                Value str = void_value();
                str.is_void = 0;
                str.is_string = 1;

                char* new_str = malloc(strlen(left_val.string_value) + strlen(right_val.string_value) + 1);
                strcpy(new_str, left_val.string_value);
                strcat(new_str, right_val.string_value);

                str.string_value = new_str;

                return str;
            }
            return number_to_value(left_val.number + right_val.number);
        } 
        else if (strcmp(node -> op, "-") == 0) {
            return number_to_value(left_val.number - right_val.number);
        } 
        else if (strcmp(node -> op, "*") == 0) {
            return number_to_value(left_val.number * right_val.number);
        } 
        else if (strcmp(node -> op, "/") == 0) {
            if (right_val.number == 0) {
                printf("Error: division by zero\n");
                return number_to_value(0);
            }
            return number_to_value(left_val.number / right_val.number);
        }else if(strcmp(node -> op, "%") == 0) {
            if (right_val.number == 0) {
                printf("Error: division by zero\n");
                return number_to_value(0);
            }

            return number_to_value(left_val.number % right_val.number);
        }

        printf("Error: unknown operator %s\n", node->op);
        return number_to_value(0);
    }

    if(node -> type == AST_BLOCK) {
        Value result;

        for(int i = 0; i < node -> count; i++) {
            result = eval(node -> block[i], table);
        }

        return result;
    }

    printf("Error: unknown node type\n");
    return number_to_value(0);
}