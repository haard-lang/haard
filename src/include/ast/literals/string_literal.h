#ifndef HAARD_AST_STRING_LITERAL_EXPRESSION_H
#define HAARD_AST_STRING_LITERAL_EXPRESSION_H

#include "literal.h"

namespace haard {
    class StringLiteral : public Literal {
    public:
        StringLiteral(Token& token);
    };
}

#endif
