all: compiler

clean:
	rm compiler flex_analyzer.o syntax_analyzer.o tree.o syntax_analyzer.tab.h syntax_analyzer.tab.c lex.yy.c syntax_analyzer.output print_visitor.o

compiler: syntax_analyzer.o flex_analyzer.o tree.o
	g++ -g -o compiler flex_analyzer.o syntax_analyzer.o  tree.o  -lfl --std=c++14

syntax_analyzer.o: syntax_analyzer.y
	bison -dt --verbose syntax_analyzer.y && g++ -g -c --std=c++14 syntax_analyzer.tab.c -o syntax_analyzer.o

flex_analyzer.o: flex_analyzer.l
	flex flex_analyzer.l && g++ -g -c lex.yy.c -o flex_analyzer.o --std=c++14

tree.o: print_visitor.o tree.cpp
	g++ -g -c tree.cpp -o tree.o --std=c++14

print_visitor.o: print_visitor.cpp
	g++ -g -c print_visitor.cpp -o print_visitor.o --std=c++14
