magenta: parser.tab.o tree.o mg_obj.o
	g++ *.o -o magenta

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l
lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

parser.tab.h: parser.tab.c
parser.tab.c: parser.y
	bison -d parser.y
parser.tab.o: parser.tab.c tree.h
	g++ -c parser.tab.c

tree.o: tree.c tree.h
	g++ -c tree.c

mg_obj.o: mg_obj.c mg_obj.h
	g++ -c mg_obj.c

clean:
	rm -f lex.yy.c parser.tab.h parser.tab.c *.o sloth
