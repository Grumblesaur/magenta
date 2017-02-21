magenta: parser.tab.o lex.yy.o tree.o mg.obj.o
	g++ -o magenta parser.tab.o lex.yy.o tree.o mg.obj.o

mg_obj.o: mg_obj.cpp mg_obj.h
	g++ -c mg_obj.cpp

parser.o: parser.tab.c tree.h mg_obj.h
	g++ -c parser.tab.c
parser.tab.h: parser.tab.c
parser.tab.c: parser.y
tree.o: tree.h tree.cpp parser.tab.h
	g++ -c tree.cpp

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

clean:
	rm tree.o mg_obj.o parser.tab.c parser.tab.h parser.tab.o lex.yy.c
	rm magenta lex.yy.o
