#ifndef HAARD_AST_CHAR_LITERAL_EXPRESSION_H
#define HAARD_AST_CHAR_LITERAL_EXPRESSION_H

#include "literal.h"

namespace haard {
    class CharLiteral : public Literal {
    public:
        CharLiteral(Token& token);
    };
}

#endif
