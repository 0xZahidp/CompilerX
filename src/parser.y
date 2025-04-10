%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.l"  // Include the lexer definitions from lexer.l
#include "symbol_table.h"  // For symbol table handling
#include "semantic_analysis.h"  // For semantic checks
#include "intermediate_code.h"  // For intermediate code generation

extern int yylex();  // Declare the lexer function
extern int yylval;   // Declare the external variable yylval

// Function to print the Abstract Syntax Tree (optional)
void print_ast(struct ASTNode* node);
%}

%union {
    int ival;
    float fval;
    char* strval;
    struct ASTNode* astnode;
}

%token <ival> NUMBER
%token <strval> IDENTIFIER
%token IF ELSE ELIF WHILE INT FLOAT RETURN PRINT ZAHID STOP END MAAX MIIN CASE ANSWER FLOOP LEAPYR TOGGLE COMM CORE RESULT DEC SQRT GCD LCM EXCG TEXT INFO PRESET

%left '+' '-'
%left '*' '/' '%'
%right '='
%left '<' '>' LEQ GEQ EQ NEQ

%start program

%%

/* Grammar Rules */

program:
    program statement
    | statement
    ;

statement:
    declaration
    | assignment
    | if_statement
    | while_statement
    | return_statement
    | print_statement
    | expression_statement
    ;

declaration:
    type IDENTIFIER ';' {
        /* Add the identifier to the symbol table */
        insert_symbol($2, $1);
    }
    ;

type:
    INT { $$ = 1; }
    | FLOAT { $$ = 2; }
    ;

assignment:
    IDENTIFIER '=' expression ';' {
        /* Perform assignment */
        printf("Assigned value to %s\n", $1);
    }
    ;

if_statement:
    IF expression block ELSE block {
        /* Handle if-else statement */
    }
    | IF expression block ELIF expression block {
        /* Handle if-elif statements */
    }
    ;

while_statement:
    WHILE expression block {
        /* Handle while loop */
    }
    ;

return_statement:
    RETURN expression ';' {
        /* Handle return statement */
    }
    ;

print_statement:
    PRINT expression ';' {
        /* Print the value of the expression */
        printf("Print: %d\n", $2);
    }
    ;

expression_statement:
    expression ';'
    ;

expression:
    IDENTIFIER {
        $$ = lookup_symbol($1);  // Look up identifier in the symbol table
    }
    | NUMBER {
        $$ = $1;
    }
    | IDENTIFIER '+' IDENTIFIER {
        $$ = $1 + $3;  // Example for addition of two identifiers (simple arithmetic)
    }
    | '(' expression ')' {
        $$ = $2;
    }
    ;

block:
    '{' program '}'
    ;

%%

/* Error handling */
int yyerror(char* s) {
    fprintf(stderr, "Error: %s\n", s);
    return 1;
}

int main() {
    yyparse();
    return 0;
}
