#ifndef HAARD_AST_PARENTHESIS_H
#define HAARD_AST_PARENTHESIS_H

#include "unary_operator.h"

namespace haard {
    class Parenthesis : public UnaryOperator {
    public:
        Parenthesis(Expression* expression=nullptr);
        Parenthesis(Token& token, Expression* expression=nullptr);
    };
}

#endif
