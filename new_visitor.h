#ifndef NEW_VISITOR_H
#define NEW_VISITOR_H

#include <SymbolTable/Table.h>

namespace tableNS {

class newVisitor : public Visitor
{
public:
    void ParseProgram(Program* root);

    virtual void visit(const Program*) override;
    virtual void visit(const MainClass*) override;
    virtual void visit(const ClassDeclaration*) override;
    virtual void visit(const VarDeclaration*) override {}
    virtual void visit(const MethodDeclaration*) override {}
    virtual void visit(const Argument*) override {}
    virtual void visit(const Statements*) override {}
    virtual void visit(const IfElseStatement*) override {}
    virtual void visit(const WhileStatement*) override {}
    virtual void visit(const SystemOutStatement*) override {}
    virtual void visit(const AssignStatement*) override {}
    virtual void visit(const ArrayAssignStatement*) override {}
    virtual void visit(const BinaryExpression*) override {}
    virtual void visit(const ArrayMemberExpression*) override {}
    virtual void visit(const ArrayLengthExpression*) override {}
    virtual void visit(const CallMemberExpression*) override {}
    virtual void visit(const IntegerExpression*) override {}
    virtual void visit(const BooleanExpression*) override {}
    virtual void visit(const ThisExpression*) override {}
    virtual void visit(const IntArrayExpression*) override {}
    virtual void visit(const ObjectExpression*) override {}
    virtual void visit(const NotExpression*) override {}
    virtual void visit(const IdExpression*) override {}
    virtual void visit(const Id*) override {}
    virtual ~Visitor() = default;

private:
    Table table;
    void printClassInfo(const ClassInfo* classInfo);
    void printVariable(const VariableInfo* varInfo);
    void printType(const TypeInfo& varInfo);
};
}
#endif
