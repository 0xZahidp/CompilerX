%{
#include "parser.tab.h"
#include <stdio.h>
%}

digit       [0-9]
id          [a-zA-Z_][a-zA-Z0-9_]*
ws          [ \t\n\r]+

%%

"full"  { return INT; }
"when"      { return IF; }
"ewhen"     { return ELSE; }
"while"     { return WHILE; }      // keep 'while' or change to 'loop'
"floop"     { return FOR; }        // new token for future use
"Result"   { return DISPLAY; } 
"Zahid" {
    printf("Zahid's ID -> 221-15-4996\n");
}



"=="                { return EQ; }
"!="                { return NEQ; }
"<="                { return LE; }
">="                { return GE; }
"<"                 { return '<'; }
">"                 { return '>'; }

"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"%"                 { return '%'; }

"="                 { return '='; }
";"                 { return ';'; }
"("                 { return '('; }
")"                 { return ')'; }
"{"                 { return '{'; }
"}"                 { return '}'; }

{digit}+            { yylval.num = atoi(yytext); return NUM; }
{id}                { yylval.id = strdup(yytext); return ID; }

{ws}                { /* ignore whitespace */ }

.                   { return yytext[0]; }

%%

int yywrap() { return 1; }
