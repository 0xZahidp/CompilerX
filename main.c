#include <stdio.h>

extern int yyparse();

int main() {
    printf("Enter your code:\n");
    yyparse();
    return 0;
}
