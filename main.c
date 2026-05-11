#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "parser.h"
#include "eval.h"

void print_ast(ASTNode* node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) printf(" ");
    if (node->type == AST_ASSIGN) {
        printf("=\n");

        for (int i = 0; i < depth + 1; i++)
            printf(" ");

        printf("%s\n", node-> name);

        print_ast(node->right, depth + 1);
    }

    if (node->type == AST_NUMBER) {
        printf("%d\n", node->value);
        return;
    }


    if (node->type == AST_BINARY_OP) {
        printf("%c\n", node->op);
        print_ast(node->left, depth + 1);
        print_ast(node->right, depth + 1);
        return;
    }

    printf("Unknown node\n");
}

int main() {
    char input[100];

    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = 0;

    Lexer lexer = init_lexer(input);
    Parser parser = init_parser(&lexer);

    ASTNode* node = parse_statement(&parser);

    if (!node) {
        printf("Parse error\n");
        return 1;
    }

    // int result = eval(node);

    print_ast(node, 0);
    // printf("%d\n", result);

    return 0;
}