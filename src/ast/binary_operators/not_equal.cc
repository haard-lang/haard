#include "ast/binary_operators/not_equal.h"

using namespace haard;

NotEqual::NotEqual(Expression* left, Expression* right) {
    set_kind(EXPR_NOT_EQUAL);
    set_left(left);
    set_right(right);
}

NotEqual::NotEqual(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_NOT_EQUAL);
    set_left(left);
    set_right(right);
    set_token(token);
}
