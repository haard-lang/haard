#include "ast/binary_operators/plus_assignment.h"

using namespace haard;

PlusAssignment::PlusAssignment(Expression* left, Expression* right) {
    set_kind(EXPR_PLUS_ASSIGNMENT);
    set_left(left);
    set_right(right);
}

PlusAssignment::PlusAssignment(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_PLUS_ASSIGNMENT);
    set_left(left);
    set_right(right);
    set_token(token);
}
