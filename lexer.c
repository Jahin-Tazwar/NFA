#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

Lexer init_lexer(char* text) {
    Lexer lexer;
    lexer.index = 0;
    lexer.text = text;
    lexer.current_char = text[0];
    return lexer;
}

void advance(Lexer* lexer) {
    lexer -> index++;

    if(lexer -> text[lexer -> index] != '\0') {
        lexer -> current_char = lexer -> text[lexer -> index];
    }else {
        lexer -> current_char = '\0';
    }
}

void skip_whitespaces(Lexer* lexer) {
    while(isspace(lexer -> current_char)) {
        advance(lexer);
    }
}

Token number(Lexer* lexer) {
    Token token;

    token.type = TOKEN_NUMBER;

    int i = 0;

    while(isdigit(lexer -> current_char)) {
        token.value[i++] = lexer -> current_char;
        advance(lexer);
    }

    token.value[i] = '\0';

    return token;
}

Token identifier(Lexer* lexer) {
    Token token;

    int i = 0;

    while(isalpha(lexer -> current_char)) {
        token.value[i++] = lexer -> current_char;
        advance(lexer);
    } 
    token.value[i] = '\0';

    if(strcmp(token.value, "let") == 0) {
        token.type = TOKEN_LET;
    }else if(strcmp(token.value, "if") == 0){
        token.type = TOKEN_IF;
    }else if(strcmp(token.value, "else") == 0){
        token.type = TOKEN_ELSE;
    }else if(strcmp(token.value, "fn") == 0){
        token.type = TOKEN_FN;
    }else {
        token.type = TOKEN_IDENTIFIER;
    }

    return token;
}

Token get_next_token(Lexer* lexer) {
    while(lexer -> current_char != '\0') {
        if(isspace(lexer -> current_char)) {
            skip_whitespaces(lexer);
            continue;
        }

        if(isdigit(lexer -> current_char)) {
            return number(lexer);
        }

        if(isalpha(lexer -> current_char)) {
            return identifier(lexer);
        }

        if(lexer -> current_char == '+') {
            advance(lexer);
            Token token;
            token.type = TOKEN_PLUS;
            strcpy(token.value, "+");
            return token;
        }

        if(lexer -> current_char == '-') {
            advance(lexer);
            Token token;
            token.type = TOKEN_MINUS;
            strcpy(token.value, "-");
            return token;
        }

        if(lexer -> current_char == '*') {
            advance(lexer);
            Token token;
            token.type = TOKEN_STAR;
            strcpy(token.value, "*");
            return token;
        }

        if(lexer -> current_char == '/') {
            advance(lexer);
            Token token;
            token.type = TOKEN_SLASH;
            strcpy(token.value, "/");
            return token;
        }

        if(lexer -> current_char == '=') {
            advance(lexer);
            if(lexer -> current_char == '='){
                advance(lexer);
                Token token;
                token.type = TOKEN_EQ;
                strcpy(token.value, "==");
                return token;
            }
            Token token;
            token.type = TOKEN_EQUAL;
            strcpy(token.value, "=");
            return token;
        }

        if(lexer -> current_char == '(') {
            advance(lexer);
            Token token;
            token.type = TOKEN_LPAREN;
            strcpy(token.value, "(");
            return token;
        }

        if(lexer -> current_char == ')') {
            advance(lexer);
            Token token;
            token.type = TOKEN_RPAREN;
            strcpy(token.value, ")");
            return token;
        }

        if(lexer -> current_char == '{') {
            advance(lexer);
            Token token;
            token.type = TOKEN_LCURLY;
            strcpy(token.value, "{");
            return token;
        }

        if(lexer -> current_char == '}') {
            advance(lexer);
            Token token;
            token.type = TOKEN_RCURLY;
            strcpy(token.value, "}");
            return token;
        }

        if(lexer -> current_char == '!') {
            advance(lexer);
            if(lexer -> current_char == '='){
                advance(lexer);
                Token token;
                token.type = TOKEN_NOTEQ;
                strcpy(token.value, "!=");
                return token;
            }
            Token token;
            token.type = TOKEN_NOT;
            strcpy(token.value, "!");
            return token;
        }

        if(lexer -> current_char == '&') {
            advance(lexer);
            if(lexer -> current_char == '&'){
                advance(lexer);
                Token token;
                token.type = TOKEN_AND;
                strcpy(token.value, "&&");
                return token;
            }
            
            Token token;
            token.type = TOKEN_UNKNOWN;
            token.value[0] = lexer->current_char;
            token.value[1] = '\0';
            return token;
        }

        if(lexer -> current_char == '|') {
            advance(lexer);
            if(lexer -> current_char == '|'){
                advance(lexer);
                Token token;
                token.type = TOKEN_OR;
                strcpy(token.value, "||");
                return token;
            }

            Token token;
            token.type = TOKEN_UNKNOWN;
            token.value[0] = lexer->current_char;
            token.value[1] = '\0';
            return token;
        }

        if(lexer -> current_char == '>') {
            advance(lexer);
            if(lexer -> current_char == '='){
                advance(lexer);
                Token token;
                token.type = TOKEN_GTE;
                strcpy(token.value, ">=");
                return token;
            }
            Token token;
            token.type = TOKEN_GT;
            strcpy(token.value, ">");
            return token;
        }

        if(lexer -> current_char == '<') {
            advance(lexer);
            if(lexer -> current_char == '='){
                advance(lexer);
                Token token;
                token.type = TOKEN_LTE;
                strcpy(token.value, "<=");
                return token;
            }
            Token token;
            token.type = TOKEN_LT;
            strcpy(token.value, "<");
            return token;
        }

        if(lexer -> current_char == ',') {
            advance(lexer);
            Token token;
            token.type = TOKEN_COMMA;
            strcpy(token.value, ",");
            return token;
        }

        Token token;
        token.type = TOKEN_UNKNOWN;
        token.value[0] = lexer->current_char;
        token.value[1] = '\0';
        advance(lexer);

        return token;
    }

    Token token;
    token.type = TOKEN_EOF;
    strcpy(token.value, "EOF");

    return token;
}