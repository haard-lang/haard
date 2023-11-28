#ifndef HAARD_AST_BITWISE_AND_H
#define HAARD_AST_BITWISE_AND_H

#include "binary_operator.h"

namespace haard {
    class BitwiseAnd : public BinaryOperator {
    public:
        BitwiseAnd(Expression* left=nullptr, Expression* right=nullptr);
        BitwiseAnd(Token& token, Expression* left=nullptr, Expression* right=nullptr);
    };
}

#endif