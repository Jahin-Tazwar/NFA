#ifndef TOKEN_H
#define TOKEN_H 

typedef enum {
    TOKEN_NUMBER,
    TOKEN_LET,         
    TOKEN_IDENTIFIER, /*|---Variable names
                    ├── Function names
                    ├── Class names
                    ├── Object names
                    └── etc.*/

    //Math operators
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_SLASH,
    TOKEN_STAR,
    TOKEN_EQUAL,

    // ()
    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_EOF, //End of file
    TOKEN_UNKNOWN // for unknown characters.
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
} Token;

#endif // !TOKEN_H