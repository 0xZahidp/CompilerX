%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex();
void yyerror(const char *msg);

#define MAX_VARS 100

typedef struct {
    char* name;
    int value;
} Var;

Var symbol_table[MAX_VARS];
int var_count = 0;

int get_var(char* name) {
    for (int i = 0; i < var_count; ++i) {
        if (strcmp(symbol_table[i].name, name) == 0)
            return symbol_table[i].value;
    }
    return 0;  // Default to 0 if not found
}

void set_var(char* name, int value) {
    for (int i = 0; i < var_count; ++i) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            symbol_table[i].value = value;
            return;
        }
    }
    symbol_table[var_count].name = name;
    symbol_table[var_count++].value = value;
}
%}

%union {
    int num;
    char* id;
}

%token <num> NUM
%token <id> ID
%token INT IF ELSE WHILE
%token FOR DISPLAY

%token EQ NEQ LE GE

%type <num> expr
%type <num> stmt expr_stmt decl_stmt assignment_stmt

%left '+' '-'
%left '*' '/' '%'
%left EQ NEQ LE GE '<' '>'

%%

program:
    program stmt
    | /* empty */
    ;

stmt:
      decl_stmt
    | assignment_stmt
    | expr_stmt
    | if_stmt
    | while_stmt
    | for_stmt
    | print_stmt
    | '{' program '}'        // support block inside control structures
    ;

decl_stmt:
    INT ID '=' expr ';'   { set_var($2, $4); printf("Declare: int %s = %d\n", $2, $4); }
    ;

assignment_stmt:
    ID '=' expr ';'       { set_var($1, $3); printf("Assign: %s = %d\n", $1, $3); }
    ;

expr_stmt:
    expr ';'              { printf("Result: %d\n", $1); }
    ;

if_stmt:
    IF '(' expr ')' stmt
    {
        if ($3 != 0) {  // Check if condition is true (non-zero)
            $5;  // Execute the statement (stmt) after the if
        }
    }
    | IF '(' expr ')' stmt ELSE stmt
    {
        if ($3 != 0) {  // If condition is true
            $5;  // Execute the statement (stmt) after the if
        } else {  // If condition is false
            $7;  // Execute the statement (stmt) after the else
        }
    }
    ;



while_stmt:
    WHILE '(' expr ')' stmt
    {
        while ($3 != 0) {  // Condition must be non-zero for the loop to run
            printf("Executing WHILE loop\n");
            $5;  // Execute the statement inside the while loop
            set_var("i", get_var("i") + 1);  // Ensure i is updated correctly after each iteration
        }
    }
    ;


for_stmt:
    FOR '(' ID '=' expr ';' expr ';' ID '=' expr ')' stmt
    {
        set_var($3, $5);  // Initialize variable $3 (ID) with value $5 (expr)
        while ($7 != 0) {  // Loop condition
            printf("Executing FOR loop\n");
            $9;   // Loop body
            set_var($3, $5);  // Update variable $3 (ID) with the new value of $5 (increment)
        }
    }
    ;

print_stmt:
    DISPLAY '(' expr ')' ';'   { printf("Output: %d\n", $3); }
    ;

expr:
      NUM                 { $$ = $1; }
    | ID                  { $$ = get_var($1); }
    | expr '+' expr       { $$ = $1 + $3; }
    | expr '-' expr       { $$ = $1 - $3; }
    | expr '*' expr       { $$ = $1 * $3; }
    | expr '/' expr       { $$ = $1 / $3; }
    | expr '%' expr       { $$ = $1 % $3; }
    | expr EQ expr        { $$ = $1 == $3; }
    | expr NEQ expr       { $$ = $1 != $3; }
    | expr LE expr        { $$ = $1 <= $3; }
    | expr GE expr        { $$ = $1 >= $3; }
    | expr '<' expr       { $$ = $1 < $3; }
    | expr '>' expr       { $$ = $1 > $3; }
    | '(' expr ')'        { $$ = $2; }
    ;

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Syntax error: %s\n", msg);
}
