#include "print_visitor.h"
#include "syntax_analyzer.tab.h"

extern Program* root;

int main(void) {
	yyparse();
	PrintVisitor* printer = new PrintVisitor("./output.gv");
	root->accept(printer);
	delete printer;	
}
