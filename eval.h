#ifndef EVAL_H
#define EVAL_H
#include "ast.h"
#include "symbol_table.h"

int eval(ASTNode* node, SymbolTable* table);

#endif // !EVAL_H