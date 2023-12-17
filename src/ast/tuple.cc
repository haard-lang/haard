#include "ast/tuple.h"

using namespace haard;

Tuple::Tuple() {
    set_kind(EXPR_TUPLE);
    expressions = new ExpressionList();
}

Tuple::~Tuple() {
    delete expressions;
}

void Tuple::add_expression(Expression* expr) {
    expressions->add_expression(expr);
}

ExpressionList* Tuple::get_expressions() {
    return expressions;
}
