#include "ast/module.h"

using namespace haard;

Module::~Module() {
    for (auto i : imports) {
        delete i;
    }
}

void Module::add_import(Import* import) {
    imports.push_back(import);
}
