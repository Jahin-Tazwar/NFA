#ifndef PARSER_H
#define PARSER_H
#include "ast.h"
#include "lexer.h"

typedef struct Parser {
    Token current_token;
    Lexer* lexer;
} Parser;

Parser init_parser(Lexer* lexer);
ASTNode* parse_factor(Parser* parser);
ASTNode* parse_term(Parser* parser);
ASTNode* parse_expression(Parser* parser);

#endif // !PARSER_H