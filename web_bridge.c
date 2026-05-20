#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#include "parser.h"
#include "eval.h"
#include "symbol_table.h"

// Static buffer to hold the result string for JS to read
static char result_buffer[1024];

EMSCRIPTEN_KEEPALIVE
const char* run_nfa(const char* input) {
    if (!input || strlen(input) == 0) {
        return "";
    }

    SymbolTable table;
    table.count = 0;
    table.parent = NULL;

    setup_builtins(&table);

    Lexer lexer = init_lexer((char*)input);
    Parser parser = init_parser(&lexer);

    Value last_result = {0};
    int found_stmt = 0;

    while (parser.current_token.type != TOKEN_EOF) {
        ASTNode* node = parse_statement(&parser);
        
        if (!node) {
            snprintf(result_buffer, sizeof(result_buffer), "Error: Parse failed.");
            return result_buffer;
        }

        last_result = eval(node, &table);
        found_stmt = 1;
    }

    if (!found_stmt) {
        return "";
    }

    if (last_result.type != VAL_VOID) {
        if (last_result.type == VAL_FUNCTION) {
            printf("<function>\n");
        } else {
            printf("%d\n", last_result.as.number);
        }
    }


    return result_buffer;
}
