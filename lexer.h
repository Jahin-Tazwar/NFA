#ifdef LEXER_H
#define LEXER_H
#include "token.h"

typedef struct {
    char* text;
    int index;
    char current_char;
} Lexer;

Lexer init_lexer(char* text);
Token get_next_token(Lexer* lexer);

#endif // DEBUG