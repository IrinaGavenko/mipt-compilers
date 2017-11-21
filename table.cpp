#include "syntax_analyzer.tab.h"
#include "new_visitor.h"

Program* root;

int main(void) {
	yyparse();
	tableNS::newVisitor visitor = new tableNS::newVisitor()
	visitor.ParseProgram(root);
}
