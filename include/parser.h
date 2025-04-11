#ifndef PARSER_H
#define PARSER_H

#include "semantic_analysis.h"
#include "ast.h"

// External function declarations
int yyparse();  // Parsing function
int yylex();    // Lexer function (from lexer.l)
int yyerror(char* s); // Error reporting function

// Parser functions
void parse_program();
void parse_statement();
void parse_declaration();

#endif
