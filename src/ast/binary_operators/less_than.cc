#include "ast/binary_operators/less_than.h"

using namespace haard;

LessThan::LessThan(Expression* left, Expression* right) {
    set_kind(EXPR_LESS_THAN);
    set_left(left);
    set_right(right);
}

LessThan::LessThan(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_LESS_THAN);
    set_left(left);
    set_right(right);
    set_token(token);
}
