#include "ast/subtyped_type.h"

using namespace haard;

SubtypedType::SubtypedType(int kind, Type* type) {
    set_kind(kind);
    set_subtype(type);
}

Type* SubtypedType::get_subtype() const {
    return subtype;
}

void SubtypedType::set_subtype(Type* newSubtype) {
    subtype = newSubtype;
}
