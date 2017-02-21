magenta: lex.yy.o parser.tab.o tree.o mg_obj.o
	g++ lex.yy.o parser.tab.o tree.o mg_obj.o -o magenta

lex.yy.o: lex.yy.c parser.tab.h
	gcc -c lex.yy.c

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

tree.o: tree.h tree.cpp mg_obj.h parser.tab.h
	g++ -c tree.cpp

parser.tab.h: parser.tab.c
parser.tab.c: parser.y tree.h mg_obj.h
	bison -d parser.y
parser.tab.o: parser.tab.c tree.h
	g++ -c parser.tab.c

tree.o: tree.c tree.h
	g++ -c tree.c

mg_obj.o: mg_obj.c mg_obj.h
	g++ -c mg_obj.c

clean:
	rm -f lex.yy.c parser.tab.h parser.tab.c *.o magenta
