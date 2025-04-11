# Compiler settings
CC = gcc
CFLAGS = -Wall -g -Iinclude
LEX = flex
BISON = bison
LEXER_FILE = src/lexer.l
PARSER_FILE = src/parser.y
OUTPUT = compiler  # Final output executable

# Object files
OBJ = src/main.o src/lexer.yy.o src/parser.tab.o src/code_generation.o src/code_emission.o \
      src/semantic_analysis.o src/symbol_table.o src/ast.o src/optimizations.o src/utils.o \
      src/intermediate_code.o

# Default target to build the project
all: $(OUTPUT)

# Rule for generating lexer file (src/lexer.yy.c) from src/lexer.l
src/lexer.yy.c: $(LEXER_FILE)
	$(LEX) -o src/lexer.yy.c $(LEXER_FILE)

# Rule for generating parser files (src/parser.tab.c and src/parser.tab.h) from src/parser.y
src/parser.tab.c src/parser.tab.h: $(PARSER_FILE)
	$(BISON) -d -o src/parser.tab.c $(PARSER_FILE)

# Rule to build the main object file
src/main.o: src/main.c include/ast.h include/semantic_analysis.h src/parser.tab.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

# Rule to build the lexer object file
src/lexer.yy.o: src/lexer.yy.c src/parser.tab.h
	$(CC) $(CFLAGS) -c src/lexer.yy.c -o src/lexer.yy.o

# Rule to build the parser object file
src/parser.tab.o: src/parser.tab.c include/ast.h include/semantic_analysis.h include/intermediate_code.h include/code_generation.h
	$(CC) $(CFLAGS) -c src/parser.tab.c -o src/parser.tab.o

# Rule to build the object file for code generation
src/code_generation.o: src/code_generation.c include/code_generation.h include/intermediate_code.h
	$(CC) $(CFLAGS) -c src/code_generation.c -o src/code_generation.o

# Rule to build the object file for code emission
src/code_emission.o: src/code_emission.c include/code_emission.h
	$(CC) $(CFLAGS) -c src/code_emission.c -o src/code_emission.o

# Rule to build the object file for semantic analysis
src/semantic_analysis.o: src/semantic_analysis.c include/semantic_analysis.h
	$(CC) $(CFLAGS) -c src/semantic_analysis.c -o src/semantic_analysis.o

# Rule to build the object file for symbol table
src/symbol_table.o: src/symbol_table.c include/symbol_table.h
	$(CC) $(CFLAGS) -c src/symbol_table.c -o src/symbol_table.o

# Rule to build the object file for AST functions
src/ast.o: src/ast.c include/ast.h
	$(CC) $(CFLAGS) -c src/ast.c -o src/ast.o

# Rule to build the object file for optimizations
src/optimizations.o: src/optimizations.c include/optimizations.h
	$(CC) $(CFLAGS) -c src/optimizations.c -o src/optimizations.o

# Rule to build the object file for utils functions
src/utils.o: src/utils.c include/utils.h
	$(CC) $(CFLAGS) -c src/utils.c -o src/utils.o

# Rule to build the object file for intermediate code generation
src/intermediate_code.o: src/intermediate_code.c include/intermediate_code.h include/ast.h
	$(CC) $(CFLAGS) -c src/intermediate_code.c -o src/intermediate_code.o

# Final linking to create the executable
$(OUTPUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ)

# Rule for cleaning up the build
clean:
	rm -f $(OBJ) src/lexer.yy.c src/parser.tab.c src/parser.tab.h $(OUTPUT)

# Rule to recompile the entire project
re: clean all

.PHONY: all clean re