#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"
#include "eval.h"
#include "symbol_table.h"

#define MAX_INPUT 256

void print_ast(ASTNode* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) printf(" ");

    if (node->type == AST_ASSIGN) {
        printf("=\n");

        for (int i = 0; i < depth + 1; i++)
            printf(" ");

        printf("%s\n", node->name);

        print_ast(node->right, depth + 1);
        return;
    }

    else if (node->type == AST_NUMBER) {
        printf("%d\n", node->value);
        return;
    }

    else if (node->type == AST_BINARY_OP) {
        printf("%s\n", node->op);

        print_ast(node->left, depth + 1);
        print_ast(node->right, depth + 1);
        return;
    }

    else if (node->type == AST_VARIABLE) {
        printf("%s\n", node->name);
        return;
    }

    printf("Unknown node\n");
}

int main() {
    SymbolTable table;
    table.count = 0;

    setup_builtins(&table);

    char input[MAX_INPUT];

    printf("NFA REPL (type 'exit' to quit)\n");

    while (1) {

        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }

        // remove newline
        input[strcspn(input, "\n")] = 0;

        // exit command
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // skip empty input
        if (strlen(input) == 0) {
            continue;
        }

        Lexer lexer = init_lexer(input);
        Parser parser = init_parser(&lexer);

        ASTNode* node = parse_statement(&parser);

        if (!node) {
            printf("Parse error\n");
            continue;
        }

        Value result = eval(node, &table);

        if (!result.is_void) {
            if (result.is_function) {
                printf("<function>\n");
            } else {
                printf("%d\n", result.number);
            }
        }
    }

    return 0;
}