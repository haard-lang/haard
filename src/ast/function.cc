#include "ast/function.h"

using namespace haard;

Function::Function() {
    set_kind(AST_FUNCTION);
    set_generics(nullptr);
    set_return_type(nullptr);
}

Function::~Function() {
    for (auto v : parameters) {
        delete v;
    }
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

Type* Function::get_return_type() const {
    return return_type;
}

void Function::set_return_type(Type* newReturn_type) {
    return_type = newReturn_type;
}

TypeList* Function::get_generics() const {
    return generics;
}

void Function::set_generics(TypeList* newGenerics) {
    generics = newGenerics;
}
