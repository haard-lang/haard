#ifndef HAARD_AST_INTEGER_LITERAL_EXPRESSION_H
#define HAARD_AST_INTEGER_LITERAL_EXPRESSION_H

#include "literal.h"

namespace haard {
    class IntegerLiteral : public Literal {
    public:
        IntegerLiteral(Token& token);
    };
}

#endif
