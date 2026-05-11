#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "parser.h"

void print_ast(ASTNode* node, int depth) {
    if(!node) return;

    for(int i = 0; i < depth; i++) printf(" ");

    if(node -> op == AST_NUMBER) {
        printf("%d\n", node -> value);
    }else {
        printf("%c\n", node -> op);
        print_ast(node -> left, depth + 1);
        print_ast(node -> right, depth + 1);
    }
}

int main() {
    char input[50];

    fgets(input, 50, stdin);

    Lexer lexer = init_lexer(input);

    Parser parser = init_parser(&lexer);

    ASTNode* tree = parse_expression(&parser);

    print_ast(tree, 0);
}