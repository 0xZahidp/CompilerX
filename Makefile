all:
	bison -d parser.y
	flex lexer.l
	gcc -o compiler main.c lex.yy.c parser.tab.c
