#include "ast/binary_operators/minus_assignment.h"

using namespace haard;

MinusAssignment::MinusAssignment(Expression* left, Expression* right) {
    set_kind(EXPR_MINUS_ASSIGNMENT);
    set_left(left);
    set_right(right);
}

MinusAssignment::MinusAssignment(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_MINUS_ASSIGNMENT);
    set_left(left);
    set_right(right);
    set_token(token);
}
