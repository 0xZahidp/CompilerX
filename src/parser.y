%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.l"  // Lexer definitions
#include "semantic_analysis.h"  // Semantic analysis functions
#include "ast.h"  // AST definitions
#include "intermediate_code.h"  // Intermediate code generation functions
#include "code_generation.h"    // Code generation functions

extern int yylex();  // Lexer function
extern int yylval;   // Lexer value (used by Flex)

void print_ast(struct ASTNode* node);  // Optional: For printing the AST
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
        /* Insert variable into symbol table */
        Symbol* existing_symbol = lookup_symbol($2);
        if (existing_symbol != NULL) {
            printf("Error: Variable '%s' already declared\n", $2);
            exit(1);
        }
        insert_symbol($2, $1);  // Insert the variable with its type
        printf("Declared variable: %s\n", $2);
    }
    ;

type:
    INT { $$ = INT_TYPE; }
    | FLOAT { $$ = FLOAT_TYPE; }
    ;

assignment:
    IDENTIFIER '=' expression ';' {
        /* Look up the variable in the symbol table */
        Symbol* symbol = lookup_symbol($1);
        if (symbol == NULL) {
            printf("Error: Undeclared variable '%s'\n", $1);
            exit(1);
        }

        // Perform type checking (expression type must match variable type)
        if (symbol->type != $3) {
            printf("Error: Type mismatch for variable '%s'\n", $1);
            exit(1);
        }

        printf("Assigned value to %s\n", $1);
    }
    ;

if_statement:
    IF expression block ELSE block {
        $$ = create_if_node($2, $4, $6);
        TAC* tac = generate_tac($$);
        generate_code(tac);  // Generate assembly-like code
        free_tac(tac);
    }
    ;

while_statement:
    WHILE expression block {
        $$ = create_while_node($2, $4);
        TAC* tac = generate_tac($$);
        generate_code(tac);  // Generate assembly-like code
        free_tac(tac);
    }
    ;

return_statement:
    RETURN expression ';' {
        $$ = create_binop_node(AST_ASSIGN, $2, NULL);
        TAC* tac = generate_tac($$);
        generate_code(tac);  // Generate assembly-like code
        free_tac(tac);
    }
    ;

print_statement:
    PRINT expression ';' {
        $$ = create_binop_node(AST_ASSIGN, $2, NULL);
        TAC* tac = generate_tac($$);
        generate_code(tac);  // Generate assembly-like code
        free_tac(tac);
    }
    ;

expression_statement:
    expression ';'
    ;

expression:
    IDENTIFIER {
        /* Look up identifier and handle semantic errors */
        Symbol* symbol = lookup_symbol($1);
        if (symbol == NULL) {
            printf("Error: Undeclared variable '%s'\n", $1);
            exit(1);
        }
        $$ = create_identifier_node($1);  // Create AST node for identifier
    }
    | NUMBER {
        $$ = create_number_node($1);  // Create AST node for number
    }
    | IDENTIFIER '+' IDENTIFIER {
        $$ = create_binop_node(AST_ADD, create_identifier_node($1), create_identifier_node($3));
    }
    | IDENTIFIER '-' IDENTIFIER {
        $$ = create_binop_node(AST_SUB, create_identifier_node($1), create_identifier_node($3));
    }
    | IDENTIFIER '*' IDENTIFIER {
        $$ = create_binop_node(AST_MUL, create_identifier_node($1), create_identifier_node($3));
    }
    | IDENTIFIER '/' IDENTIFIER {
        $$ = create_binop_node(AST_DIV, create_identifier_node($1), create_identifier_node($3));
    }
    | '(' expression ')' {
        $$ = $2;  // Parenthesized expression
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
    // Initialize the symbol table
    symbol_table = NULL;

    yyparse();  // Start parsing
    free_symbol_table();  // Free symbol table after parsing

    return 0;
}
