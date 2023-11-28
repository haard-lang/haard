#ifndef HAARD_BINARY_OPERATOR_H
#define HAARD_BINARY_OPERATOR_H

#include "ast/expression.h"

namespace haard {
    class BinaryOperator : public Expression {
    public:
        BinaryOperator();
        BinaryOperator(int kind, Token& oper, Expression* left, Expression* right);
        ~BinaryOperator();

        Expression* get_left() const;
        void set_left(Expression* newLeft);

        Expression* get_right() const;
        void set_right(Expression* newRight);

    private:
        Expression* left;
        Expression* right;
    };
}

#endif
