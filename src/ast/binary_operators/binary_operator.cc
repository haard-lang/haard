#include "ast/binary_operators/binary_operator.h"

using namespace haard;

BinaryOperator::BinaryOperator() {
    set_left(nullptr);
    set_right(nullptr);
}

BinaryOperator::BinaryOperator(int kind, Token &oper, Expression* left, Expression* right) {
    set_kind(kind);
    set_token(oper);
    set_left(left);
    set_right(right);
}

BinaryOperator::~BinaryOperator() {
    delete left;
    delete right;
}

Expression* BinaryOperator::get_left() const {
    return left;
}

void BinaryOperator::set_left(Expression* newLeft) {
    left = newLeft;
}

Expression* BinaryOperator::get_right() const {
    return right;
}

void BinaryOperator::set_right(Expression* newRight) {
    right = newRight;
}
