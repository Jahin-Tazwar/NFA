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
    TOKEN_EQUAL, // for assignment
    
    //Compare operators
    TOKEN_EQ, // ==
    TOKEN_GT, // >
    TOKEN_LT, // <
    TOKEN_NOTEQ, // !=
    TOKEN_GTE, //>=
    TOKEN_LTE, //<=

    //Logical operators
    TOKEN_NOT, //!
    TOKEN_AND, // &&
    TOKEN_OR, // ||

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