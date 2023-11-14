#ifndef HAARD_PARSER_H
#define HAARD_PARSER_H

#include <string>
#include <vector>
#include "ast/ast.h"
#include "token/token.h"

namespace haard {
    class Parser {
    public:
        Module* read(std::string path);

    private:
        Module* module;
        std::vector<Token> tokens;
    };
}

#endif
