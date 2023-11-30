#ifndef HAARD_AST_FLOAT_LITERAL_EXPRESSION_H
#define HAARD_AST_FLOAT_LITERAL_EXPRESSION_H

#include "literal.h"

namespace haard {
    class FloatLiteral : public Literal {
    public:
        FloatLiteral(Token& token);
    };
}

#endif
