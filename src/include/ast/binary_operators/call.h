#ifndef HAARD_AST_CALL_H
#define HAARD_AST_CALL_H

#include "binary_operator.h"

namespace haard {
    class Call : public BinaryOperator {
    public:
        Call(Expression* left=nullptr, Expression* right=nullptr);
        Call(Token& token, Expression* left=nullptr, Expression* right=nullptr);
    };
}

#endif