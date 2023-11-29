#ifndef HAARD_UNNARY_OPERATOR_H
#define HAARD_UNNARY_OPERATOR_H

#include "ast/expression.h"

namespace haard {
    class UnaryOperator : public Expression {
    public:
        UnaryOperator();
        UnaryOperator(int kind, Token& oper, Expression* expression);
        ~UnaryOperator();

        Expression* get_expression() const;
        void set_expression(Expression* newExpression);

    private:
        Expression* expression;
    };
}

#endif
