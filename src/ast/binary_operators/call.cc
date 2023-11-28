#include "ast/binary_operators/call.h"

using namespace haard;

Call::Call(Expression* left, Expression* right) {
    set_kind(EXPR_CALL);
    set_left(left);
    set_right(right);
}

Call::Call(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_CALL);
    set_left(left);
    set_right(right);
    set_token(token);
}
