#include <stdio.h>
#include "stdlib.h"
#include "parser.h"

Parser init_parser(Lexer* lexer) {
    Parser parser;
    parser.current_token = get_next_token(lexer);
    parser.lexer = lexer;

    return parser;
}

void advance_parser(Parser* parser) {
    parser -> current_token = get_next_token(parser -> lexer);
}

// (5+2) * 3
ASTNode* parse_factor(Parser* parser) {
    ASTNode* node = NULL;
    if(parser -> current_token.type == TOKEN_NUMBER) {
        node = create_number(atoi(parser -> current_token.value));
        advance_parser(parser);
    }else if(parser -> current_token.type == TOKEN_LPAREN) {
        advance_parser(parser); // skip (

        node = parse_expression(parser); //build tree for the whole expression in ()

        if (parser->current_token.type != TOKEN_RPAREN) {
            printf("Error: missing ')'\n");
            return NULL;
        }

        advance_parser(parser); //skip )
    }else {
        printf("Error: unexpected token\n");
        return NULL;
    }
    return node;
}

ASTNode* parse_term(Parser* parser) {
    ASTNode* left = parse_factor(parser);

    while(parser -> current_token.type == TOKEN_STAR || parser -> current_token.type == TOKEN_SLASH) {   
        char op = parser -> current_token.value[0];
        advance_parser(parser);
        ASTNode* right = parse_factor(parser);
        left = create_op(op, left, right);
    }

    return left;
}

ASTNode* parse_expression(Parser* parser) {
    ASTNode* left = parse_term(parser);

    while(parser -> current_token.type == TOKEN_PLUS || parser -> current_token.type == TOKEN_MINUS) {
        char op = parser -> current_token.value[0];
        advance_parser(parser);
        ASTNode* right = parse_term(parser);
        left = create_op(op, left, right);
    }

    return left;
}