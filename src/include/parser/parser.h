#ifndef HAARD_PARSER_H
#define HAARD_PARSER_H

#include <string>
#include <vector>
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

    private:
        void advance();
        bool lookahead(int kind);
        bool match(int kind);
        bool expect(int kind);

    private:
        Module* module;
        std::vector<Token> tokens;
        Token matched;
        int idx;
    };
}

#endif
