magenta: lex.yy.o parser.tab.o tree.o mg_types.o mg_string.o interpreter.o \
mg_ops.o mg_error.o mg_list.o
	g++ -g lex.yy.o parser.tab.o tree.o mg_types.o mg_string.o \
	interpreter.o mg_ops.o mg_error.o mg_list.o -o magenta

lex.yy.o: lex.yy.c parser.tab.h
	g++ -g -c lex.yy.c

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.o: parser.tab.c tree.h
	g++ -g -c -std=c++11 parser.tab.c

interpreter.o: interpreter.h interpreter.cpp tree.h mg_types.h \
parser.tab.h except.h mg_string.h mg_ops.h mg_error.h
	g++ -g -c -std=c++11 interpreter.cpp

mg_types.o: mg_types.h mg_types.cpp
	g++ -g -c -std=c++11 mg_types.cpp

mg_string.o: mg_string.h mg_string.cpp
	g++ -g -c -std=c++11 mg_string.cpp

mg_list.o: mg_list.h mg_list.cpp
	g++ -g -c -std=c++11 mg_list.cpp

mg_ops.o: mg_ops.h mg_error.h mg_ops.cpp
	g++ -g -c -std=c++11 mg_ops.cpp

mg_error.o: mg_error.cpp mg_error.h
	g++ -g -c -std=c++11 mg_error.cpp

tree.o: tree.h tree.cpp parser.tab.h
	g++ -g -c -std=c++11 tree.cpp

parser.tab.h: parser.tab.c
parser.tab.c: parser.y tree.h interpreter.h
	bison -dv parser.y

clean:
	rm -f lex.yy.c parser.tab.h parser.tab.c *.o magenta *.output
