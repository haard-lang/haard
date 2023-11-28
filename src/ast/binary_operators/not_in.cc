#include "ast/binary_operators/not_in.h"

using namespace haard;

NotIn::NotIn(Expression* left, Expression* right) {
    set_kind(EXPR_NOT_IN);
    set_left(left);
    set_right(right);
}

NotIn::NotIn(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_NOT_IN);
    set_left(left);
    set_right(right);
    set_token(token);
}
