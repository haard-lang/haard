#include "ast/binary_operators/cast.h"

using namespace haard;

Cast::Cast(Expression* left, Expression* right) {
    set_kind(EXPR_CAST);
    set_left(left);
    set_right(right);
}

Cast::Cast(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_CAST);
    set_left(left);
    set_right(right);
    set_token(token);
}
