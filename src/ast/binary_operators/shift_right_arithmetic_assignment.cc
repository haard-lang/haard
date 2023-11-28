#include "ast/binary_operators/shift_right_arithmetic_assignment.h"

using namespace haard;

ShiftRightArithmeticAssignment::ShiftRightArithmeticAssignment(Expression* left, Expression* right) {
    set_kind(EXPR_SHIFT_RIGHT_ARITHMETIC_ASSIGNMENT);
    set_left(left);
    set_right(right);
}

ShiftRightArithmeticAssignment::ShiftRightArithmeticAssignment(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_SHIFT_RIGHT_ARITHMETIC_ASSIGNMENT);
    set_left(left);
    set_right(right);
    set_token(token);
}
