#include <stdio.h>
#include "lexer.h"

int main() {

    char input[] = "let x = 5 + 3";

    Lexer lexer = init_lexer(input);

    Token token;

    while (1) {
        token = get_next_token(&lexer);

        printf("Type: %d, Value: %s\n",
               token.type,
               token.value);

        if (token.type == TOKEN_EOF)
            break;
    }

    return 0;
}