#ifndef HAARD_AST_INDEX_H
#define HAARD_AST_INDEX_H

#include "binary_operator.h"

namespace haard {
    class Index : public BinaryOperator {
    public:
        Index(Expression* left=nullptr, Expression* right=nullptr);
        Index(Token& token, Expression* left=nullptr, Expression* right=nullptr);
    };
}

#endif