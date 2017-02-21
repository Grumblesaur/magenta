magenta: lex.yy.o parser.tab.o tree.o mg_obj.o
	g++ lex.yy.o parser.tab.o tree.o mg_obj.o -o magenta

lex.yy.o: lex.yy.c parser.tab.h
	gcc -c lex.yy.c

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.h: parser.tab.c
parser.tab.c: parser.y tree.h mg_obj.h
	bison -d parser.y
parser.tab.o: parser.tab.c tree.h mg_obj.h
	g++ -c parser.tab.c

tree.o: tree.cpp tree.h parser.tab.h
	g++ -c tree.cpp

mg_obj.o: mg_obj.cpp mg_obj.h
	g++ -c mg_obj.cpp

clean:
	rm -f lex.yy.c parser.tab.h parser.tab.c *.o magenta
