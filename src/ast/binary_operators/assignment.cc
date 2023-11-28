#include "ast/binary_operators/assignment.h"

using namespace haard;

Assignment::Assignment(Expression* left, Expression* right) {
    set_kind(EXPR_ASSIGNMENT);
    set_left(left);
    set_right(right);
}

Assignment::Assignment(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_ASSIGNMENT);
    set_left(left);
    set_right(right);
    set_token(token);
}
