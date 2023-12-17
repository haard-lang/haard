#ifndef HAARD_SEQUENCE_H
#define HAARD_SEQUENCE_H

#include "ast/expression.h"
#include "ast/expression_list.h"

namespace haard {
    class Sequence : public Expression {
    public:
        Sequence();
        ~Sequence();

    public:
        void add_expression(Expression* expr);
        ExpressionList* get_expressions();

    private:
        ExpressionList* expressions;
    };
}

#endif
