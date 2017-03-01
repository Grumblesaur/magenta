magenta: lex.yy.o parser.tab.o tree.o mg_obj.o interpreter.o
	g++ lex.yy.o parser.tab.o tree.o mg_obj.o interpreter.o -o magenta

lex.yy.o: lex.yy.c parser.tab.h
	g++ -g -c lex.yy.c

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.o: parser.tab.c tree.h
	g++ -g -c parser.tab.c

interpreter.o: interpreter.h interpreter.cpp tree.h mg_obj.h parser.tab.h
	g++ -g -c -std=c++11 interpreter.cpp

mg_obj.o: mg_obj.h mg_obj.cpp tree.h parser.tab.h
	g++ -g -c mg_obj.cpp

tree.o: tree.h tree.cpp parser.tab.h
	g++ -g -c tree.cpp

parser.tab.h: parser.tab.c
parser.tab.c: parser.y tree.h interpreter.h
	bison -dv parser.y

clean:
	rm -f lex.yy.c parser.tab.h parser.tab.c *.o magenta
