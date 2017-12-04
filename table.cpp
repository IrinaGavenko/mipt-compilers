#include "VSymbolTable/TableVisitor.h"
#include "tokens.h"

extern std::unique_ptr<AST::Program> program;

int main(void) {
  yyparse();
  SymbolTable::TableVisitor visitor;
  visitor.ParseProgram(program.get());
}
