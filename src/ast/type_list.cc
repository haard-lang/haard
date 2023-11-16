#include "ast/type_list.h"

using namespace haard;

TypeList::TypeList(int kind) {
    set_kind(kind);
}

void TypeList::add_type(Type* type) {
    types.push_back(type);
}

Type* TypeList::get_type(int idx) {
    return types[idx];
}

int TypeList::types_count() {
    return types.size();
}
