#ifndef HAARD_AST_LOGICAL_NOT_H
#define HAARD_AST_LOGICAL_NOT_H

#include "unary_operator.h"

namespace haard {
    class LogicalNot : public UnaryOperator {
    public:
        LogicalNot(Expression* expression=nullptr);
        LogicalNot(Token& token, Expression* expression=nullptr);
    };
}

#endif