#include "ast/unary_operators/parenthesis.h"

using namespace haard;

Parenthesis::Parenthesis(Expression* expression) {
    set_kind(EXPR_PARENTHESIS);
    set_expression(expression);
}

Parenthesis::Parenthesis(Token& token, Expression* expression) {
    set_kind(EXPR_PARENTHESIS);
    set_expression(expression);
    set_token(token);
}
