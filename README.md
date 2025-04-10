# CompilerX: A Compiler Design Project for a Custom Programming Language

CompilerX is a C-based compiler designed for a custom programming language. It demonstrates key compiler construction concepts, including lexical analysis, syntax parsing, semantic analysis, code generation, and optimization. The project uses **Flex** for lexical analysis, **Bison** for syntax parsing, and custom components for semantic analysis and code generation.

## Features

- **Lexical Analysis**: Scans and tokenizes source code into meaningful tokens such as keywords, identifiers, operators, and constants.
- **Syntax Analysis**: Verifies the syntax of the source code and generates an Abstract Syntax Tree (AST).
- **Semantic Analysis**: Checks for undeclared variables, type mismatches, and ensures the program follows the rules of the language.
- **Intermediate Code Generation**: Transforms the AST into an intermediate representation that is easier to optimize and translate into machine code.
- **Code Optimization**: Implements optimization techniques such as constant folding and dead code elimination.
- **Code Generation**: Converts the intermediate code into assembly or machine code.
- **Error Handling**: Reports errors during lexical analysis, syntax analysis, and semantic analysis.

## Technologies Used

- **Programming Language**: C
- **Compiler Tools**:

- **Flex** (Lexical Analysis)

- **Bison** (Syntax Parsing)

- **GCC** (Compilation)

- **Version Control**: Git and GitHub for collaboration and version management

## Project Structure

The repository is organized into the following directories:

- **`src/`**: Contains the source code for the compiler phases (lexer, parser, semantic analysis, code generation, etc.).
- **`include/`**: Contains header files for the project.
- **`test/`**: Contains test programs and expected outputs for validation.
- **`docs/`**: Documentation for the project, including design and final report.
- **`Makefile`**: Automates the build process.
- **`README.md`**: Provides an overview of the project, setup instructions, and usage.

## Getting Started

To get started with CompilerX:

1. **Clone the repository**:

```bash

git clone https://github.com/0xZahidp/CompilerX.git
```

2. Navigate to the project directory:

```
cd CompilerX
```

3. Build the project:

Use the provided Makefile to build the project:

```
make
```

4. Run the compiler:

After building, you can compile source files by running:

```
./compiler <source-file.c>
```

Testing

Test programs and expected outputs can be found in the test/ directory. To run tests:

1. Navigate to the test/ directory.

2. Run the test script (if available) or manually compile and check the output.

Future Improvements

- Extended Language Features: Add support for functions, arrays, structs, and other complex features.
- Error Reporting: Improve error handling and provide more detailed error messages.
- Advanced Optimization: Implement advanced optimization techniques such as loop unrolling and constant propagation.
- GUI Interface: Add a simple graphical interface for easier interaction with the compiler.

Contact

For questions or contributions, please contact [0xZahidp](https://github.com/0xZahidp).

### Key Sections in this `README.md`:

- **Project Description**: A brief overview of what the project is and its key features.
- **Technologies Used**: List of tools and libraries that are being used.
- **Project Structure**: An explanation of how the project is organized.
- **Getting Started**: Instructions on how to clone the repo, build, and run the project.
- **Testing**: Information on how to test the compiler with the provided test cases.
- **Future Improvements**: A few areas where the project can be extended.
- **License**: Details about the license for the project.
- **Contact**: How others can reach you for contributions or questions.
