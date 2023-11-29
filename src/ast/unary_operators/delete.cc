#include "ast/unary_operators/delete.h"

using namespace haard;

Delete::Delete(Expression* expression) {
    set_kind(EXPR_DELETE);
    set_expression(expression);
}

Delete::Delete(Token& token, Expression* expression) {
    set_kind(EXPR_DELETE);
    set_expression(expression);
    set_token(token);
}
