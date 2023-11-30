#ifndef HAARD_AST_DOUBLE_LITERAL_EXPRESSION_H
#define HAARD_AST_DOUBLE_LITERAL_EXPRESSION_H

#include "literal.h"

namespace haard {
    class DoubleLiteral : public Literal {
    public:
        DoubleLiteral(Token& token);
    };
}

#endif
