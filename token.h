#ifdef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_LET,
    TOKEN_IDENTIFIER,

    //Math operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_EQUAL,

    TOKEN_LPAREN,// (
    TOKEN_RPAREN,// )

    TOKEN_EOF, // End Of File
    TOKEN_UNNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
} Token;

#endif // DEBUG