#ifndef HAARD_PARSER_H
#define HAARD_PARSER_H

#include <string>
#include <vector>
#include <stack>
#include "ast/ast.h"
#include "token/token.h"

namespace haard {
    class Parser {
    public:
        Parser();

    public:
        Module* read(std::string path);

    public:
        Module* parse_module();
        Import* parse_import();

        Function* parse_function();
        void parse_parameters(Function* function);

        Type* parse_type();

    private:
        void advance();
        bool lookahead(int kind, int offset=0);
        bool match(int kind);
        bool expect(int kind);

        void indent();
        void dedent();

        bool has_parameters();

    private:
        Module* module;
        Token matched;
        int idx;

        std::vector<Token> tokens;
        std::stack<int> indent_stack;
    };
}

#endif
