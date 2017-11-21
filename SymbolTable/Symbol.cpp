#include "Symbol.h"
#include <string>
#include <unordered_map>

namespace tableNS {

    Position::Position(int _x, int _y) :
            x(_x),
            y(_y) {
    }

    std::string Position::ToString() const {
        return "(" + std::to_string(y) + "," + std::to_string(x) + ")";
    }

    StringSymbol *StringSymbol::GetIntern(const std::string &name) {
        static std::unordered_map <std::string, std::unique_ptr<StringSymbol>> strings;
        auto result = strings.find(name);
        if (result == strings.end()) {
            strings.insert(std::make_pair(name,
                                      std::unique_ptr<StringSymbol>(new StringSymbol(name))));
        }

        return strings.find(name)->second.get();
    }

    Symbol::Symbol(std::string name, Position &position) :
            name(StringSymbol::GetIntern(name)),
            position(position) {}

    Symbol::Symbol(StringSymbol *name, Position &position) :
            name(name),
            position(position) {}

    bool Symbol::operator==(const Symbol &a) {
        return &a == this;
    }

    bool Symbol::operator!=(const Symbol &a) {
        return &a != this;
    }

}
