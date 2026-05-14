#ifndef EVAL_H
#define EVAL_H
#include "ast.h"
#include "symbol_table.h"

Value eval(ASTNode* node, SymbolTable* table);
void setup_builtins(SymbolTable* table);

#endif // !EVAL_H