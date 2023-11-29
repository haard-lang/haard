#ifndef HAARD_AST_NEW_H
#define HAARD_AST_NEW_H

#include "unary_operator.h"

namespace haard {
    class New : public UnaryOperator {
    public:
        New(Expression* expression=nullptr);
        New(Token& token, Expression* expression=nullptr);
    };
}

#endif