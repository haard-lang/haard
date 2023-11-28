#ifndef HAARD_AST_ARROW_H
#define HAARD_AST_ARROW_H

#include "binary_operator.h"

namespace haard {
    class Arrow : public BinaryOperator {
    public:
        Arrow(Expression* left=nullptr, Expression* right=nullptr);
        Arrow(Token& token, Expression* left=nullptr, Expression* right=nullptr);
    };
}

#endif