# Custom-C-Compiler-Translation
# Custom Word Compiler

Welcome to the **Custom Word Compiler** project! This compiler is designed to parse and evaluate a custom programming language where traditional C keywords are replaced by unique, user-friendly keywords. It handles variable declarations, assignments, arithmetic operations, control structures (like `if`, `while`, `for`), and output via the `display` statement.

## Features
- **Custom Keywords**: 
  - `wholenum` → `int`
  - `when` → `if`
  - `alter` → `else`
  - `cycle` → `for`
  - `display` → print output
- **Basic Arithmetic Operations**: Supports `+`, `-`, `*`, `/`, `%` for expressions.
- **Relational Operators**: Handles comparison operations like `==`, `!=`, `<`, `>`, `<=`, `>=`.
- **Control Flow**: Supports `if`, `else`, `while`, and `for` loops with conditions.
- **Variable Declaration and Assignment**: Declare variables using `wholenum` and assign them values with `=`.
  
## How It Works

1. **Lexical Analysis (Lexer)**: 
   - The lexer (using **Flex**) reads the input source code and breaks it into **tokens**.
   - Tokens are mapped to corresponding actions like variable declarations, assignments, or expressions.

2. **Parsing (Parser)**: 
   - The parser (using **Bison**) processes the tokens and evaluates them according to the grammar rules.
   - It supports variable declarations, arithmetic operations, control structures, and output.

3. **Symbol Table**: 
   - The symbol table stores the values of variables declared within the program, ensuring that they are updated and accessible during execution.

## Installation

To set up and run the compiler on your local machine, follow these steps:

### Prerequisites
- **Flex** (for lexical analysis)
- **Bison** (for parsing)
- **GCC** or **Clang** (for compiling the code)

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/custom-word-compiler.git
```
