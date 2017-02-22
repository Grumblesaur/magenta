magenta: lex.yy.o parser.tab.o tree.o mg_obj.o
	g++ lex.yy.o parser.tab.o tree.o mg_obj.o -o magenta

lex.yy.o: lex.yy.c parser.tab.h
	g++ -c lex.yy.c

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.o: parser.tab.c tree.h
	g++ -c parser.tab.c

mg_obj.o: mg_obj.h mg_obj.cpp tree.h
	g++ -c mg_obj.cpp

tree.o: tree.h tree.cpp parser.tab.h
	g++ -c tree.cpp

parser.tab.h: parser.tab.c
parser.tab.c: parser.y tree.h
	bison -d parser.y

clean:
	rm -f lex.yy.c parser.tab.h parser.tab.c *.o magenta