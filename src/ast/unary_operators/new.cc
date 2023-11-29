#include "ast/unary_operators/new.h"

using namespace haard;

New::New() {
    set_kind(EXPR_NEW);
    set_arguments(nullptr);
}

New::~New() {
    delete arguments;
}

ExpressionList* New::get_arguments() const {
    return arguments;
}

void New::set_arguments(ExpressionList* newArguments) {
    arguments = newArguments;
}
