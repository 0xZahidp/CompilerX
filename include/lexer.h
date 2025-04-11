#ifndef LEXER_H
#define LEXER_H

extern int yylex();  // Lexer function declaration
extern char* yytext; // Global variable that holds the current token

// Token definitions
#define IF 1
#define ELSE 2
#define IDENTIFIER 3
#define NUMBER 4
#define ASSIGN 5
#define PLUS 6
#define MINUS 7
#define MUL 8
#define DIV 9
#define LPAREN 10
#define RPAREN 11

#endif