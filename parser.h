#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct {
    Lexer* lexer;
    Token current_token;
} Parser;

Parser init_parser(Lexer* lexer);
ASTNode* parse_expression(Parser* parser);

#endif // !PARSER_H
