#include "ast/binary_operators/in.h"

using namespace haard;

In::In(Expression* left, Expression* right) {
    set_kind(EXPR_IN);
    set_left(left);
    set_right(right);
}

In::In(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_IN);
    set_left(left);
    set_right(right);
    set_token(token);
}
