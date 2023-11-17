#ifndef HAARD_EXPRESSION_STATEMENT_H
#define HAARD_EXPRESSION_STATEMENT_H

#include "ast/statement.h"
#include "ast/expression.h"

namespace haard {
    class ExpressionStatement : public Statement {
    public:
        ExpressionStatement(Expression* expr=nullptr);
        ~ExpressionStatement();

    public:
        void set_expression(Expression* expr);
        Expression* get_expression();

    private:
        Expression* expression;
    };
}

#endif
