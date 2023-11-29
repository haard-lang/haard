#ifndef HAARD_AST_POS_DECREMENT_H
#define HAARD_AST_POS_DECREMENT_H

#include "unary_operator.h"

namespace haard {
    class PosDecrement : public UnaryOperator {
    public:
        PosDecrement(Expression* expression=nullptr);
        PosDecrement(Token& token, Expression* expression=nullptr);
    };
}

#endif