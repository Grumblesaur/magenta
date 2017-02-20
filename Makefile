magenta: lex.yy.c parser.tab.c
	gcc lex.yy.c parser.tab.c -o magenta

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.h: parser.tab.c
parser.tab.c: parser.y
	bison -d parser.y

clean:
	rm -f lex.yy.c parser.tab.h parser.tab.c *.o sloth