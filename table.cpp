#include "syntax_analyzer.tab.h"
#inlcude ""

Program* root;

int main(void) {
	yyparse();
	tableNS::... visitor = new tableNS::...
	...
}
