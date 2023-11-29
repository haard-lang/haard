#include "ast/unary_operators/new.h"

using namespace haard;

New::New(Expression* expression) {
    set_kind(EXPR_NEW);
    set_expression(expression);
}

New::New(Token& token, Expression* expression) {
    set_kind(EXPR_NEW);
    set_expression(expression);
    set_token(token);
}
