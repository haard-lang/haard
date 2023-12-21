#ifndef HAARD_TUPLE_LITERAL_H
#define HAARD_TUPLE_LITERAL_H

#include "ast/expression.h"
#include "ast/expression_list.h"

namespace haard {
    class TupleLiteral : public Expression {
    public:
        TupleLiteral();
        ~TupleLiteral();

    public:
        void add_expression(Expression* expr);
        ExpressionList* get_expressions();

    private:
        ExpressionList* expressions;
    };
}

#endif
