#ifndef HAARD_AST_CAST_H
#define HAARD_AST_CAST_H

#include "binary_operator.h"

namespace haard {
    class Cast : public Expression {
    public:
        Cast(Expression* expression=nullptr, Type* type=nullptr);
        Cast(Token& token, Expression* expression=nullptr, Type* type=nullptr);
        ~Cast();

    public:
        Expression* get_expression() const;
        void set_expression(Expression* newExpression);

    private:
        Expression* expression;
    };
}

#endif
