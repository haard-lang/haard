#include "ast/unary_operators/unary_operator.h"

using namespace haard;

UnaryOperator::UnaryOperator() {
    set_expression(nullptr);
}

UnaryOperator::UnaryOperator(int kind, Token& oper, Expression* expression) {
    set_kind(kind);
    set_token(oper);
    set_expression(expression);
}

UnaryOperator::~UnaryOperator() {
    delete expression;
}

Expression* UnaryOperator::get_expression() const {
    return expression;
}

void UnaryOperator::set_expression(Expression* newExpression) {
    expression = newExpression;
}
