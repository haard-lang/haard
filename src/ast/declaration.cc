#include "ast/declaration.h"

using namespace haard;

const Token& Declaration::get_name() const {
    return name;
}

void Declaration::set_name(const Token& newName) {
    name = newName;
}
