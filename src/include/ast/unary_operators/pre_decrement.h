#ifndef HAARD_AST_PRE_DECREMENT_H
#define HAARD_AST_PRE_DECREMENT_H

#include "unary_operator.h"

namespace haard {
    class PreDecrement : public UnaryOperator {
    public:
        PreDecrement(Expression* expression=nullptr);
        PreDecrement(Token& token, Expression* expression=nullptr);
    };
}

#endif