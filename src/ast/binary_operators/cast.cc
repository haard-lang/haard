#include "ast/binary_operators/cast.h"

using namespace haard;

Cast::Cast(Expression* expression, Type* type) {
    set_kind(EXPR_CAST);
    set_expression(expression);
    set_type(type);
}

Cast::Cast(Token& token, Expression* expression, Type* type) {
    set_kind(EXPR_CAST);
    set_expression(expression);
    set_type(type);
    set_token(token);
}

Cast::~Cast() {
    delete expression;
}

Expression* Cast::get_expression() const {
    return expression;
}

void Cast::set_expression(Expression* newExpression) {
    expression = newExpression;
}
