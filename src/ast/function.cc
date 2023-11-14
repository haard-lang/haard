#include "ast/function.h"

using namespace haard;

Function::Function() {
    set_kind(AST_FUNCTION);
}

void Function::add_parameter(Variable* param) {
    parameters.push_back(param);
}

int Function::parameters_count() {
    return parameters.size();
}

Variable* Function::get_parameter(int idx) {
    return parameters[idx];
}
