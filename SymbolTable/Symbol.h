#pragma once

#include <string>
#include <memory>

namespace tableNS {

    class Position {
    public:
        Position(int _x, int _y);
	std::string ToString() const;
    private:
        int x;
        int y;
    };

    class StringSymbol {
    public:
        static StringSymbol *GetIntern(const std::string &name);
        const std::string &GetString() const { return body; }

    private:
        std::string body;
        StringSymbol(std::string name) : body(name) {}
        StringSymbol(const StringSymbol &) = delete;

        void operator=(const StringSymbol &) = delete;
    };

    class Symbol {
    public:
        Symbol(std::string name, Position &position);

        Symbol(StringSymbol *name, Position &position);

        Symbol(const Symbol &) = delete;

        void operator=(const Symbol &) = delete;

        bool operator==(const Symbol &a);

        bool operator!=(const Symbol &a);

        virtual ~Symbol() {};

        const StringSymbol *GetName() const { return name; }

        const Position &GetPosition() const { return position; }

    protected:
        const StringSymbol *name;
        const Position position;

    };

}
