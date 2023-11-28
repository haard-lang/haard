#include "ast/binary_operators/times_assignment.h"

using namespace haard;

TimesAssignment::TimesAssignment(Expression* left, Expression* right) {
    set_kind(EXPR_TIMES_ASSIGNMENT);
    set_left(left);
    set_right(right);
}

TimesAssignment::TimesAssignment(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_TIMES_ASSIGNMENT);
    set_left(left);
    set_right(right);
    set_token(token);
}
