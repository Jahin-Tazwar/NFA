# NFA Programming Language

Welcome to **NFA**, a lightweight, dynamically typed interpreted programming language designed to be embedded within WebAssembly (WASM) and compiled via C. NFA features a highly modern, C/Rust-inspired syntax, functions, imperative loops, block-scoped variables, and native built-ins.

This guide will teach you everything you need to know to write, run, and understand NFA.

---

## 🚀 Quick Start (Compilation)

NFA can be run in two environments: as a terminal CLI, or securely in a web browser using WebAssembly.

### 1. Terminal CLI
To compile the terminal REPL, use any standard C compiler (like GCC):
\`\`\`bash
gcc main.c ast.c lexer.c parser.c eval.c symbol_table.c -o lang
./lang
\`\`\`
*(Note: The terminal REPL currently evaluates line-by-line. To run multi-line scripts, either use the web interface or pipe a file into the executable: `cat script.nfa | ./lang`)*

### 2. WebAssembly (WASM)
To build the web module, use the Emscripten compiler (`emcc`):
\`\`\`bash
emcc web_bridge.c ast.c lexer.c parser.c eval.c symbol_table.c \
  -o frontend/public/nfa.js \
  -s EXPORTED_FUNCTIONS='["_run_nfa"]' \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -O3
\`\`\`

---

## 📖 Language Reference

### 1. Built-in I/O
NFA comes with native functions built into the runtime. You can print output to the console using the `print()` function.
\`\`\`javascript
print(42)
print(100 + 50)
\`\`\`

### 2. Variables & Scope
NFA enforces explicit variable declaration. You must use the `let` keyword to create a new variable. 
If a variable already exists, you can update it by assigning to it directly (without `let`). Variables are block-scoped and evaluate dynamically.

\`\`\`javascript
// Declaration
let count = 10
let multiplier = 5

// Reassignment (Update)
count = count * multiplier
print(count) // 50
\`\`\`

### 3. Math & Logic
NFA fully supports standard mathematical operations and comparison operators. It strictly respects the standard order of operations (PEMDAS).
\`\`\`javascript
let math_result = (5 + 5) * (20 / 2)
let is_greater = 10 > 5
\`\`\`

### 4. Conditionals (Expressions)
Inspired by Rust, `if` statements in NFA are **expressions**. This means an `if` block evaluates to a value and can be assigned directly to a variable.
\`\`\`javascript
let threshold = 50
let status = if (threshold >= 50) 1 else 0
print(status)
\`\`\`

### 5. Imperative Loops
NFA supports standard `while` loops for repetitive logic. The scope within a while loop is automatically managed—variables declared inside the loop will not leak to the outer scope, but you can freely update outer variables!
\`\`\`javascript
let x = 5
while (x > 0) {
    print(x)
    x = x - 1
}
print(0) // Liftoff!
\`\`\`

### 6. Functions & Recursion
You can define your own reusable logic blocks using the `fn` keyword. 
NFA functions **automatically return** the result of their last evaluated expression. There is no need for an explicit `return` keyword.

\`\`\`javascript
// A standard function
fn multiply(a, b) {
    a * b
}
print(multiply(10, 10))

// A recursive function
fn factorial(n) {
    if (n == 0) 
        1 
    else 
        n * factorial(n - 1)
}
print(factorial(5)) // 120
\`\`\`

### 7. Comments
You can document your code using double-slash syntax.
\`\`\`javascript
// This is a comment!
let x = 10 // This works too
\`\`\`

---

*NFA is a continuously evolving language designed for learning, speed, and cross-environment execution.*
