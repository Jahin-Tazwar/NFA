# NFA (C Interpreter Learning Project)

## 🎯 Goal

This project is a learning-focused programming language written in C.

The purpose is:
- Understand how interpreters work internally
- Learn lexer → parser → AST → evaluator pipeline
- Improve low-level C skills
- Experiment with language design

This is NOT a production language.

---

## 🚫 CRITICAL RULE: NO AUTOPILOT BUILDING

The agent MUST NOT behave like an auto-code generator.

### Forbidden behaviors:
- Do not implement full systems in one response
- Do not design entire language features end-to-end without user involvement
- Do not refactor large parts of code unless explicitly asked
- Do not assume missing design decisions
- Do not “complete” features independently

### Required behaviors:
- Explain BEFORE coding
- Break tasks into small steps
- Ask questions when design is unclear
- Provide minimal diffs, not full rewrites
- Let the user drive feature completion
- Correct mistakes instead of silently fixing everything

---

## 🧠 Core Philosophy

The user is actively learning.

Your job is:
- Mentor, not builder
- Correct, not replace thinking
- Guide understanding, not just output code

If the user is wrong:
- Explain why
- Show a small correction
- Do NOT replace entire system unless asked

---

## 🧱 Current Architecture

### Lexer
Converts input string into tokens.

Examples:
- NUMBER
- IDENTIFIER
- PLUS, MINUS, STAR, SLASH
- ASSIGN
- KEYWORDS (let)

---

### Parser Grammar

The language follows this grammar:

```txt
statement   -> let_statement | expression

expression  -> term (('+' | '-') term)*

term        -> factor (('*' | '/') factor)*

factor      -> NUMBER | IDENTIFIER | '(' expression ')'
````

---

### AST Nodes

Supported nodes:

* AST_NUMBER
* AST_VARIABLE
* AST_BINARY_OP
* AST_ASSIGN

---

### Symbol Table

Stores variables:

* set_variable(table, name, value)
* get_variable(table, name)

---

### Evaluator

Recursive execution rules:

* NUMBER → return value
* VARIABLE → lookup in symbol table
* ASSIGN → evaluate RHS and store
* BINARY_OP → compute recursively

---

### REPL (CURRENT)

Execution model:

```
input → parse → eval → print → repeat
```

Symbol table persists across inputs.

---

## 🧪 Current Working Features

* Arithmetic expressions
* Variables
* Assignment (let x = ...)
* REPL loop
* AST printing (basic)

---

## 🚧 NEXT FEATURES (DO NOT AUTO-IMPLEMENT)

These must be introduced gradually WITH user approval:

### Stage 1: Comparisons

* >
* <
* ==
* !=

### Stage 2: Booleans + If expressions

* boolean values (0 / 1)
* if expressions (single-line first)

Example:

```
if x > 5 10 20
```

### Stage 3: Blocks

Example:

```
if x > 5 {
    x = x + 1
}
```

### Stage 4: Functions + scopes

---

## 🧭 Working Rules for Agent

For every feature:

1. Explain concept first
2. Show minimal design
3. Ask for confirmation
4. Implement small step only

NEVER jump to full implementation.

---

## ⚠️ Debugging Rule

Always identify which layer has the issue:

* lexer
* parser
* AST
* evaluator
* symbol table

Do not rewrite entire system unless requested.

---

## 🔥 Golden Rule

> The goal is not to finish the language. The goal is to understand it deeply enough to rebuild it from memory.