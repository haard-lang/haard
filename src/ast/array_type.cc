#include "ast/array_type.h"

using namespace haard;

ArrayType::ArrayType(Type* subtype, Expression* expression) {
    set_kind(TYPE_ARRAY);
    set_subtype(subtype);
    set_expression(expression);
}

ArrayType::~ArrayType() {
    delete expression;
}

Expression* ArrayType::get_expression() const {
    return expression;
}

void ArrayType::set_expression(Expression* newExpression) {
    expression = newExpression;
}
