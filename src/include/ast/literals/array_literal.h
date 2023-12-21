#ifndef HAARD_AST_ARRAY_LITERAL_EXPRESSION_H
#define HAARD_AST_ARRAY_LITERAL_EXPRESSION_H

#include "literal.h"
#include "ast/expression_list.h"

namespace haard {
    class ArrayLiteral : public Literal {
    public:
        ArrayLiteral();
        ~ArrayLiteral();

    public:
        void add_expression(Expression* expr);

        ExpressionList* get_expressions() const;
        void set_expressions(ExpressionList* newExpressions);

    private:
        ExpressionList* expressions;
    };
}

#endif
