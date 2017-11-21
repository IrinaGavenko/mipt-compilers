#include "new_visitor.h"
#include "SymbolTable/DeclarationException.h"
#include <iostream>

namespace tableNS {
void newVisitor::ParseProgram(Program* root)
{
    root->accept(this);
    for(auto className = table.GetClassesNames().begin();
        className != table.GetClassesNames().end(); ++className)
    {
        try {
            std::string name = (*className)->GetString();
            std::cout << "class " << name << ":" << std::endl;
            auto classInfo = table.GetClass(name, Position(0,0));
            table.AddClassToScope(name, Position(0,0));
            printClassInfo(classInfo);
            table.FreeLastScope();
            std::cout << std::endl;
        } catch(DeclarationException e) {
            std::cout << "Declaration error:" << e.what() << std::endl;
        }
    }
}

void newVisitor::visit(const Program* node)
{
    node->main->accept(this);
    for (auto class_el = node->classes.begin(); class_el != node->classes.end(); class_el++){
        class_el->accept(this);
    }
}

void newVisitor::visit(const MainClass* node)
{}

void newVisitor::visit(const ClassDeclaration* node)
{
    auto newClass = new ClassInfo(node->ClassName->Name, fromCoords(node->Coords()));
    if(node->SuperName.get() != nullptr) {
        newClass->AddSuperClassName(node->SuperName->Name);
    }
    auto varDeclarations = node->VarDeclarations.get();
    if(varDeclarations != nullptr) {
        auto& varSequence = varDeclarations->SequenceList;
        for(auto var = varSequence.begin(); var != varSequence.end(); ++var) {
            newClass->AddVariableInfo(new VariableInfo(var->get()->Identifier->Name,
                                                       fromCoords(var->get()->Coords()),
                                                       fromType(var->get()->VarType.get())));
        }
    }
    auto methodDeclarations = node->MethodDeclarations.get();
    if(methodDeclarations != nullptr) {
        auto& methodSequence = methodDeclarations->SequenceList;
        for(auto method = methodSequence.begin(); method != methodSequence.end(); ++method) {
            auto methodInfo = new MethodInfo(method->get()->MethodName->Name,
                                             fromCoords(method->get()->Coords()),
                                             fromType(method->get()->ReturnType.get()),
                                             method->get()->QualifierType->QualifierEnum == AST::Q_Public ? Q_Public : Q_Private);
            auto argDeclarations = method->get()->Arguments.get();
            if(argDeclarations != nullptr) {
                auto& args = argDeclarations->SequenceList;
                for(auto arg = args.begin(); arg != args.end(); ++arg) {
                    methodInfo->AddArgInfo(new VariableInfo(arg->get()->Identifier->Name,
                                                            fromCoords(arg->get()->Coords()),
                                                            fromType(arg->get()->VarType.get())));
                }
            }
            auto varDeclarations = method->get()->VarDeclarations.get();
            if(varDeclarations != nullptr) {
                auto& localVariables = varDeclarations->SequenceList;
                for(auto var = localVariables.begin(); var != localVariables.end(); ++var) {
                    methodInfo->AddVariableInfo(new VariableInfo(var->get()->Identifier->Name,
                                                               fromCoords(var->get()->Coords()),
                                                               fromType(var->get()->VarType.get())));
                }
            }
            newClass->AddMethodInfo(methodInfo);
        }
    }
    table.AddClass(newClass, fromCoords(node->Coords()));
}

void newVisitor::printClassInfo(const ClassInfo* classInfo)
{
    if(classInfo->GetSuperClassName() != nullptr) {
        std::cout << "  Super: " << classInfo->GetSuperClassName()->GetString() << std::endl;
        auto superClass = table.GetClass(classInfo->GetSuperClassName()->GetString(), Position(0, 0));
        printClassInfo(superClass);
    }

    for(auto varName = classInfo->GetVarsNames().begin();
        varName != classInfo->GetVarsNames().end(); ++varName)
    {
        std::cout << "    ";
        auto variable = table.GetVariable((*varName)->GetString(), Position(0, 0));
        printVariable(variable);
    }

    for(auto methodName = classInfo->GetMethodNames().begin();
        methodName != classInfo->GetMethodNames().end(); ++methodName) {
        auto method = table.GetMethod((*methodName)->GetString(), Position(0, 0));
        table.AddMethodToScope(method->GetName()->GetString(), Position(0, 0));
        std::cout << "    " << (method->GetQualifier() == Q_Public ? "public " : "private ");
        printType(method->GetReturnType());
        std::cout << method->GetName()->GetString() << std::endl;
        std::cout << "      Args:" << std::endl;
        auto& args= method->GetArgsName();
        for(auto arg = args.begin(); arg != args.end(); ++arg) {
            auto var = table.GetVariable((*arg)->GetString(), Position(0, 0));
            std::cout << "        ";
            printVariable(var);
        }
        std::cout << "      Local vars:" << std::endl;
        auto& vars = method->GetVarsName();
        for(auto var = vars.begin(); var != vars.end(); ++var) {
            auto varInfo = table.GetVariable((*var)->GetString(), Position(0, 0));
            std::cout << "        ";
            printVariable(varInfo);
        }
        table.FreeLastScope();
    }
}

void newVisitor::printVariable(const VariableInfo* varInfo)
{
    printType(varInfo->GetType());
    std::cout << " " << varInfo->GetName()->GetString() << std::endl;
}

void newVisitor::printType(const TypeInfo &type)
{
    switch (type.GetType()) {
    case VT_Int:
        std::cout << "int ";
        break;
    case VT_IntArray:
        std::cout << "int[] ";
        break;
    case VT_Boolean:
        std::cout << "boolean ";
        break;
    case VT_UserClass:
        std::cout << "class " << type.GetUserClass()->GetString();
        break;
    default:
        break;
    }
}
}
