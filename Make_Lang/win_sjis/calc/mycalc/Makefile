CC=gcc

mycalc:mycalc.y mycalc.l
	yacc -dv mycalc.y
	lex mycalc.l
	$(CC) -o mycalc y.tab.c lex.yy.c

clean:
	rm -rf y.output y.tab.c y.tab.h lex.yy.c mycalc
