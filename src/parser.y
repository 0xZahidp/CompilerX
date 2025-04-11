%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic_analysis.h"
#include "ast.h"
#include "intermediate_code.h"
#include "code_generation.h"

extern int yylex();
int yyerror(char* s) {
    fprintf(stderr, "Error: %s\n", s);
    return 1;
}

void print_ast(struct ASTNode* node); // Optional AST printer
%}

%union {
    int ival;
    float fval;
    char* strval;
    struct ASTNode* astnode;
}

// Tokens with types
%token <ival> NUMBER
%token <strval> IDENTIFIER
%token IF ELSE ELIF WHILE INT FLOAT RETURN PRINT ZAHID STOP END MAAX MIIN CASE ANSWER FLOOP LEAPYR TOGGLE COMM CORE RESULT DEC SQRT GCD LCM EXCG TEXT INFO PRESET

// Precedence and associativity
%left '+' '-' 
%left '*' '/' '%' 
%right '=' 
%left '<' '>' LEQ GEQ EQ NEQ

// Declare return types of nonterminals
%type <astnode> program statement_list statement declaration assignment if_statement while_statement return_statement print_statement expression expression_statement block
%type <ival> type

%start program

%%

program:
    statement_list { $$ = $1; }
    ;

statement_list:
    statement_list statement {
        $$ = create_block_node($1, $2); // Chain statements into a block
    }
    | statement {
        $$ = $1;
    }
    | /* empty */ {
        $$ = NULL; // Empty program is a null AST node
    }
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
        Symbol* existing_symbol = lookup_symbol($2);
        if (existing_symbol != NULL) {
            fprintf(stderr, "Error: Variable '%s' already declared\n", $2);
            exit(1);
        }
        insert_symbol($2, $1);
        $$ = create_decl_node($2, $1);
        printf("Declared variable: %s\n", $2);
        free($2); // Free the string allocated by lexer
    }
    ;

type:
    INT { $$ = INT_TYPE; }
    | FLOAT { $$ = FLOAT_TYPE; }
    ;

assignment:
    IDENTIFIER '=' expression ';' {
        Symbol* symbol = lookup_symbol($1);
        if (symbol == NULL) {
            fprintf(stderr, "Error: Undeclared variable '%s'\n", $1);
            exit(1);
        }
        $$ = create_assign_node($1, $3);
        printf("Assigned value to %s\n", $1);
        free($1); // Free the string allocated by lexer
    }
    ;

if_statement:
    IF expression block ELSE block {
        $$ = create_if_node($2, $3, $5);
        TAC* tac = generate_tac($$);
        generate_code(tac);
        free_tac(tac);
    }
    | IF expression block {
        $$ = create_if_node($2, $3, NULL); // No else block
    }
    ;

while_statement:
    WHILE expression block {
        $$ = create_while_node($2, $3);
        TAC* tac = generate_tac($$);
        generate_code(tac);
        free_tac(tac);
    }
    ;

return_statement:
    RETURN expression ';' {
        $$ = create_return_node($2);
        TAC* tac = generate_tac($$);
        generate_code(tac);
        free_tac(tac);
    }
    ;

print_statement:
    PRINT expression ';' {
        $$ = create_print_node($2);
        TAC* tac = generate_tac($$);
        generate_code(tac);
        free_tac(tac);
    }
    ;

expression_statement:
    expression ';' { $$ = $1; }
    ;

expression:
    IDENTIFIER {
        Symbol* symbol = lookup_symbol($1);
        if (symbol == NULL) {
            fprintf(stderr, "Error: Undeclared variable '%s'\n", $1);
            exit(1);
        }
        $$ = create_identifier_node($1);
        free($1); // Free the string allocated by lexer
    }
    | NUMBER {
        $$ = create_number_node($1);
    }
    | expression '+' expression {
        $$ = create_binop_node(AST_ADD, $1, $3);
    }
    | expression '-' expression {
        $$ = create_binop_node(AST_SUB, $1, $3);
    }
    | expression '*' expression {
        $$ = create_binop_node(AST_MUL, $1, $3);
    }
    | expression '/' expression {
        $$ = create_binop_node(AST_DIV, $1, $3);
    }
    | '(' expression ')' {
        $$ = $2;
    }
    ;

block:
    '{' statement_list '}' {
        $$ = $2; // The block's AST is the statement list
    }
    ;

%%
