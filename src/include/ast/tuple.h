#ifndef HAARD_TUPLE_H
#define HAARD_TUPLE_H

#include "ast/expression.h"
#include "ast/expression_list.h"

namespace haard {
    class Tuple : public Expression {
    public:
        Tuple();
        ~Tuple();

    public:
        void add_expression(Expression* expr);
        ExpressionList* get_expressions();

    private:
        ExpressionList* expressions;
    };
}

#endif
