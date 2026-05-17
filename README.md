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
  -s MODULARIZE=1 \
  -s EXPORT_NAME="createNfaModule" \
  -s STACK_SIZE=524288 \
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

### 2. Variables & Data Types
NFA enforces explicit variable declaration. You must use the `let` keyword to create a new variable. 
NFA is dynamically typed and supports Numbers, Strings, and Arrays. Variables are block-scoped. 
Strings can be dynamically concatenated using the `+` operator.

\`\`\`javascript
// Declaration
let count = 10
let msg = "Hello " + "World" // "Hello World"
let list = [1, 2, "three"]

// Reassignment (Update)
count = count * 5
print(count) 
\`\`\`

### 3. Arrays & Built-ins
NFA supports composite Arrays that can hold any data type, including nested arrays. Elements can be read and written in-place using bracket indexing. You can query the length of arrays (and strings!) using the `len()` built-in function.

\`\`\`javascript
let my_list = [10, "Gold", [1, 2]]

// Indexing and Mutability
print(my_list[0]) // Reads 10
my_list[0] = 50 // Updates in-place
print(my_list) // [50, "Gold", [1, 2]]

// Length querying
print(len(my_list)) // 3
print(len("NFA")) // 3
\`\`\`

### 4. Math & Logic
NFA fully supports standard mathematical operations (including modulo `%`) and comparison operators. It strictly respects the standard order of operations (PEMDAS).
\`\`\`javascript
let math_result = (5 + 5) * (20 / 2)
let mod_result = 10 % 3 // 1
let is_greater = 10 > 5
\`\`\`

### 5. Conditionals (Expressions)
Inspired by Rust, `if` statements in NFA are **expressions**. This means an `if` block evaluates to a value and can be assigned directly to a variable.
\`\`\`javascript
let threshold = 50
let status = if (threshold >= 50) 1 else 0
print(status)
\`\`\`

### 6. Imperative Loops
NFA supports standard `while` loops for repetitive logic. The scope within a while loop is automatically managed—variables declared inside the loop will not leak to the outer scope, but you can freely update outer variables!
\`\`\`javascript
let x = 5
while (x > 0) {
    print(x)
    x = x - 1
}
print(0) // Liftoff!
\`\`\`

### 7. Functions & Recursion
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

### 8. Comments
You can document your code using double-slash syntax.
\`\`\`javascript
// This is a comment!
let x = 10 // This works too
\`\`\`

---

*NFA is a continuously evolving language designed for learning, speed, and cross-environment execution.*
