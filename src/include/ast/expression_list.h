#ifndef HAARD_AST_EXPRESSION_LIST_H
#define HAARD_AST_EXPRESSION_LIST_H

#include <vector>
#include "ast/expression.h"

namespace haard {
    class ExpressionList {
        public:
            ~ExpressionList();

        public:
            Expression* get_expression(int idx);

            void add_expression(Expression* expression);
            int expressions_count();
            
        private:
            std::vector<Expression*> expressions;
    };
}

#endif
