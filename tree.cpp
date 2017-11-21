#include "print_visitor.h"
#include "syntax_analyzer.tab.h"

Program* root;

int main(void) {
	yyparse();
	PrintVisitor* printer = new PrintVisitor("./tree_output.gv");
	root->accept(printer);
	delete printer;	
}
