#ifndef HAARD_AST_NEW_H
#define HAARD_AST_NEW_H

#include "ast/expression.h"
#include "ast/expression_list.h"

namespace haard {
    class New : public Expression {
    public:
        New();
        ~New();

        ExpressionList* get_arguments() const;
        void set_arguments(ExpressionList* newArguments);

    private:
        ExpressionList* arguments;
    };
}

#endif
