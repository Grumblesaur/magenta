magenta: parser.tab.o lex.yy.o tree.o mg.obj.o
	g++ -o magenta parser.tab.o lex.yy.o tree.o mg.obj.o

tree.o: tree.cpp tree.h
	g++ -c tree.cpp

mg_obj.o: mg_obj.cpp mg_obj.h
	g++ -c mg_obj.cpp

parser.o: parser.tab.c
	g++ -c parser.tab.c
parser.tab.h: parser.tab.c
parser.tab.c: parser.y
	bison -d parser.y

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

lex.yy.c: lexer.l
	flex lexer.l

clean:
	rm tree.o mg_obj.o parser.tab.c parser.tab.h lex.yy.c magenta
