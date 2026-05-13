#ifndef PARSER_H
#define PARSER_H
#include "ast.h"
#include "lexer.h"
#include "symbol_table.h"

typedef struct Parser {
    Token current_token;
    Lexer* lexer;
} Parser;

Parser init_parser(Lexer* lexer);
ASTNode* parse_factor(Parser* parser);
ASTNode* parse_term(Parser* parser);
ASTNode* parse_expression(Parser* parser);
ASTNode* parse_statement(Parser* parser);
ASTNode* parse_comparison(Parser* parser);
ASTNode* parse_logical(Parser* parser);
ASTNode* parse_if(Parser* parser);
ASTNode* parse_block(Parser* parser);

#endif // !PARSER_H