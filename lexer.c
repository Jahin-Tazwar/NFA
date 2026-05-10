#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

Lexer init_lexer(char* text) {
	Lexer lexer;
	lexer.text = text;
	lexer.index = 0;
	lexer.current_char = text[0];
	return lexer;
}

void advance(Lexer* lexer) {
	lexer -> index++; // Simillar to (*lexer).index++ (Gets the index)

	if(lexer -> text[lexer -> index] != '\0') {
		lexer -> current_char = lexer -> text[lexer -> index];
	}else {
		lexer -> current_char = '\0';
	}
}

void skip_whitespaces(Lexer* lexer) {
	while(lexer -> current_char == ' ') {
		advance(lexer);
	}
}

Token number(Lexer* lexer) {
	Token token;
	token.type = TOKEN_NUMBER;

	int i = 0;

	while(isdigit(lexer -> current_char)) {
		token.value[i++] = lexer -> current_char; //token's value becomes the current char and i increments.
		advance(lexer);
	}

	token.value[i] = '\0';

	return token;
}

Token identifier(Lexer* lexer) {
	Token token;

	int i = 0;

	while(isalnum(lexer -> current_char)){ //Checks if the character is alphanumeric (abc/0123)
		token.value[i++] = lexer -> current_char;
		advance(lexer);
	}

	token.value[i] = '\0';

	if(strcmp(token.value, "let") == 0) {
		token.type = TOKEN_LET;
	}else {
		token.type = TOKEN_IDENTIFIER;
	}

	return token;
}

Token get_next_token(Lexer* lexer) {
	while(lexer -> current_char != '\0') {
		if(lexer -> current_char == ' ') {
			skip_whitespaces(lexer);
			continue;
		}

		if(isdigit(lexer -> current_char)) {
			return number(lexer);
		}

		if(isalnum(lexer -> current_char)) {
			return identifier(lexer);
		}

		if(lexer -> current_char == '+') {
			advance(lexer);
			Token token = {TOKEN_PLUS, "+"}; // same as token.type and token.value
			return token;
		}

		if(lexer -> current_char == '=') {
			advance(lexer);
			Token token = {TOKEN_EQUAL, "="};
			return token;
		}

		advance(lexer);
		Token token = {TOKEN_UNKNOWN, "?"};
		return token;
	}

	Token token = {TOKEN_EOF, "EOF"};
	return token;
}