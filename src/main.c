#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "lexer.h"
#include "semantic_analysis.h"
#include "intermediate_code.h"
#include "code_generation.h"

extern FILE* yyin;  // Input file for the lexer

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source-file>\n", argv[0]);
        return 1;
    }

    // Open the source code file for reading
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Start the parsing process
    printf("Parsing and compiling source file: %s\n", argv[1]);
    yyparse();  // Starts the parsing and compilation process

    // Clean up and close the file
    fclose(yyin);

    return 0;
}
