#ifndef HAARD_AST_CAST_H
#define HAARD_AST_CAST_H

#include "binary_operator.h"

namespace haard {
    class Cast : public BinaryOperator {
    public:
        Cast(Expression* left=nullptr, Expression* right=nullptr);
        Cast(Token& token, Expression* left=nullptr, Expression* right=nullptr);
    };
}

#endif