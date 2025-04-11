# CompilerX Design Document

## Project Overview

**CompilerX** is a simple compiler built in C for a custom programming language. The compiler takes source code written in a simplified language and translates it into assembly-like code. The main purpose of this project is to demonstrate key concepts of compiler construction, including lexical analysis, syntax parsing, semantic analysis, intermediate code generation, and code emission.

## Compiler Architecture

### 1. **Lexical Analysis (Lexer)**

The lexer (generated using **Flex**) is responsible for scanning the source code and breaking it down into tokens. The lexer reads characters from the source code and groups them into meaningful tokens such as keywords, operators, identifiers, and literals.

- **File**: `lexer.l`
- **Tool**: Flex

### 2. **Syntax Analysis (Parser)**

The parser (generated using **Bison**) takes the token stream produced by the lexer and checks if the tokens follow the correct syntax based on the grammar defined in the parser rules. If the input source code is syntactically valid, the parser generates an **Abstract Syntax Tree (AST)**.

- **File**: `parser.y`
- **Tool**: Bison

### 3. **Semantic Analysis**

The semantic analysis phase ensures that the source code adheres to the rules of the language beyond just syntax. It checks for undeclared variables, type mismatches, and other logical errors in the code. The symbol table is used to store and manage variable declarations.

- **File**: `semantic_analysis.c` and `semantic_analysis.h`

### 4. **Intermediate Code Generation**

After the syntax and semantic analysis phases, the compiler generates an intermediate representation (IR), usually in the form of **Three-Address Code (TAC)**. TAC is a simplified representation of the program that is easier to optimize and translate into machine code or assembly.

- **File**: `intermediate_code.c` and `intermediate_code.h`

### 5. **Code Generation**

The code generation phase takes the intermediate code and translates it into assembly-like code that can be further assembled into machine code. The code generator emits the corresponding assembly instructions, such as loading values into registers and performing arithmetic operations.

- **File**: `code_generation.c` and `code_generation.h`

### 6. **Code Emission**

After generating the assembly-like code, the code emission phase is responsible for emitting the final code to a file or console. This includes writing the code to a file for later assembly or directly printing it for simulation.

- **File**: `code_emission.c` and `code_emission.h`

## Key Components

### Symbol Table

The symbol table stores information about variables, such as their name, type, and scope. The symbol table is used throughout the compiler to check if variables are declared before they are used and to ensure that the types match during assignments.

### Optimizations

The compiler includes basic optimizations like **constant folding** (evaluating constant expressions at compile-time) and **dead code elimination** (removing code that doesn't affect the program’s outcome).

- **File**: `optimizations.c` and `optimizations.h`

---

## Compiler Workflow

1. **Input**: A source code file (`.c` file) is provided as input.
2. **Lexical Analysis**: The lexer reads the source code and produces tokens.
3. **Syntax Analysis**: The parser analyzes the tokens based on the grammar and generates an Abstract Syntax Tree (AST).
4. **Semantic Analysis**: The AST is checked for semantic errors such as undeclared variables and type mismatches.
5. **Intermediate Code Generation**: The AST is translated into Three-Address Code (TAC), an intermediate representation.
6. **Code Generation**: The TAC is translated into assembly-like code.
7. **Code Emission**: The assembly-like code is written to a file or printed to the console.

## Future Work

1. **Optimization Improvements**: Implement more advanced optimization techniques such as constant propagation, loop unrolling, and register allocation.
2. **Target-Specific Code Generation**: Add support for different target architectures, including x86 and ARM.
3. **Error Handling**: Improve error handling for syntax and semantic errors with detailed messages and line numbers.
4. **Support for Additional Language Features**: Add support for more complex language features like functions, arrays, and structs.

---

## Conclusion

The **CompilerX** project is a simple yet functional compiler that demonstrates core compiler construction principles. With further development, this project can be extended to support a broader set of features and optimizations, making it a powerful tool for compiling custom programming languages.
