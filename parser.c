#include <stdio.h>
#include "stdlib.h"
#include "string.h"
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

ASTNode* parse_factor(Parser* parser) {
    ASTNode* node = NULL;
    if(parser -> current_token.type == TOKEN_NUMBER) {
        node = create_number(atoi(parser -> current_token.value));
        advance_parser(parser);
    }else if(parser -> current_token.type == TOKEN_IDENTIFIER) {
        char value[64];
        strcpy(value, parser -> current_token.value);
        advance_parser(parser);

        // For func calls
        if(parser -> current_token.type == TOKEN_LPAREN) {
            advance_parser(parser); // skip (
            ASTNode* args[16];
            int arg_count = 0;

            while(parser -> current_token.type != TOKEN_RPAREN) {
                args[arg_count++] = parse_if(parser);

                if(parser -> current_token.type == TOKEN_COMMA) {
                    advance_parser(parser);
                }
            }
            advance_parser(parser); // skip )
            
            return create_call(value, args, arg_count);
        }

        ASTNode* node = create_variable(value);
        return node;
    }else if(parser -> current_token.type == TOKEN_NOT){
        char op[8] = "!";
        advance_parser(parser);
        ASTNode* right = parse_factor(parser);

        return create_op(op, NULL, right);
    }else if(parser -> current_token.type == TOKEN_LPAREN) {
        advance_parser(parser); // skip (

        node = parse_if(parser); //build tree for the whole expression in ()

        if (parser->current_token.type != TOKEN_RPAREN) {
            printf("Error: missing ')'\n");
            return NULL;
        }

        advance_parser(parser); //skip )
    }else if(parser -> current_token.type == TOKEN_LCURLY){
        return parse_block(parser);
    }else {
        printf("Error: unexpected token\n");
        advance_parser(parser);
        return NULL;
    }
    return node;
}

ASTNode* parse_term(Parser* parser) {
    ASTNode* left = parse_factor(parser);

    while(parser -> current_token.type == TOKEN_STAR || parser -> current_token.type == TOKEN_SLASH) {   
        char op[8];
        strcpy(op, parser -> current_token.value);
        advance_parser(parser);
        ASTNode* right = parse_factor(parser);
        left = create_op(op, left, right);
    }

    return left;
}

ASTNode* parse_expression(Parser* parser) {
    ASTNode* left = parse_term(parser);

    while(parser -> current_token.type == TOKEN_PLUS || parser -> current_token.type == TOKEN_MINUS) {
        char op[8];
        strcpy(op, parser -> current_token.value);
        advance_parser(parser);
        ASTNode* right = parse_term(parser);
        left = create_op(op, left, right);
    }

    return left;
}

ASTNode* parse_statement(Parser* parser) {
    if(parser -> current_token.type == TOKEN_FN){
        return parse_function(parser);
    }

    if(parser -> current_token.type == TOKEN_LET) {
        advance_parser(parser);
        if (parser->current_token.type != TOKEN_IDENTIFIER) {
            printf("Expected identifier\n");
            return NULL;
        }
        char variable[64];
        strcpy(variable, parser -> current_token.value);
        advance_parser(parser);
        if (parser->current_token.type != TOKEN_EQUAL) {
            printf("Expected '='\n");
            return NULL;
        }

        advance_parser(parser);

        ASTNode* value = parse_if(parser);
        return create_assignment(variable, value);    
   }
   return parse_if(parser);
}

ASTNode* parse_comparison(Parser* parser) {
    ASTNode* left = parse_expression(parser);

    while(parser -> current_token.type == TOKEN_EQ || parser -> current_token.type == TOKEN_NOTEQ || parser -> current_token.type == TOKEN_GT || parser -> current_token.type == TOKEN_LT || parser -> current_token.type == TOKEN_GTE || parser -> current_token.type == TOKEN_LTE) {
        char op[8];
        strcpy(op, parser -> current_token.value);
        advance_parser(parser);
        ASTNode* right = parse_expression(parser);
        left = create_op(op, left, right);
    }

    return left;
}

ASTNode* parse_logical(Parser* parser) {
    ASTNode* left = parse_comparison(parser);
    
    while(parser -> current_token.type == TOKEN_AND || parser -> current_token.type == TOKEN_OR) {
        char op[8];
        strcpy(op, parser -> current_token.value);
        advance_parser(parser);
        ASTNode* right = parse_comparison(parser);
        left = create_op(op, left, right);
    }

    return left;
}


ASTNode* parse_if(Parser* parser) {
    if(parser -> current_token.type == TOKEN_IF) {
        advance_parser(parser);

        ASTNode* condition = parse_logical(parser);
        ASTNode* true_branch = parse_logical(parser);
        ASTNode* false_branch = NULL;

        if(parser -> current_token.type == TOKEN_ELSE) {
            advance_parser(parser);
            false_branch = parse_logical(parser);
        }

        return create_if(condition, true_branch, false_branch);
    }

    return parse_logical(parser);
}

ASTNode* parse_block(Parser* parser) {
    if(parser -> current_token.type == TOKEN_LCURLY) {
        advance_parser(parser);
        ASTNode* nodes[64];

        int count = 0;
        while(parser -> current_token.type != TOKEN_RCURLY && parser -> current_token.type != TOKEN_EOF) {
            ASTNode* node = parse_statement(parser);
            nodes[count] = node;
            count++;
        }

        if(parser -> current_token.type == TOKEN_RCURLY) {
            advance_parser(parser);
            return create_block(nodes, count);
        }
    }

    return parse_if(parser);
}

ASTNode* parse_function(Parser* parser) {
    advance_parser(parser); // Skip 'fn'

    char name[64];
    strcpy(name, parser->current_token.value);
    advance_parser(parser);

    advance_parser(parser); // Skip '('
    char params[16][64];
    int param_count = 0;

    while (parser->current_token.type != TOKEN_RPAREN) {
        if (parser->current_token.type == TOKEN_IDENTIFIER) {
            strcpy(params[param_count++], parser->current_token.value);
            advance_parser(parser);
        }
        
        if (parser->current_token.type == TOKEN_COMMA) {
            advance_parser(parser);
        }
    }
    advance_parser(parser); // Skip ')'

    ASTNode* body = parse_block(parser);

    return create_function(name, params, param_count, body);
}