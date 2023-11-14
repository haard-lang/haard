#include "ast/generics.h"

using namespace haard;


void Generics::add_type(Type* type) {
    types.push_back(type);
}

Type* Generics::get_type(int idx) {
    return types[idx];
}

int Generics::types_count() {
    return types.size();
}
