#include "ast/module.h"

using namespace haard;

Module::Module() {
    set_kind(AST_MODULE);
}

Module::~Module() {
    for (auto i : imports) {
        delete i;
    }

    for (auto f : functions) {
        delete f;
    }
}

void Module::add_import(Import* import) {
    imports.push_back(import);
    declarations.push_back(import);
}

int Module::imports_count() {
    return imports.size();
}

Import* Module::get_import(int idx) {
    return imports[idx];
}

void Module::add_function(Function* function) {
    functions.push_back(function);
    declarations.push_back(function);
}

int Module::functions_count() {
    return functions.size();
}

Function* Module::get_function(int idx) {
    return functions[idx];
}

int Module::declarations_count() {
    return declarations.size();
}

Declaration* Module::get_declaration(int idx) {
    return declarations[idx];
}

