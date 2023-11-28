#ifndef HAARD_AST_DOT_H
#define HAARD_AST_DOT_H

#include "binary_operator.h"

namespace haard {
    class Dot : public BinaryOperator {
    public:
        Dot(Expression* left=nullptr, Expression* right=nullptr);
        Dot(Token& token, Expression* left=nullptr, Expression* right=nullptr);
    };
}

#endif