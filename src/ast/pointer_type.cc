#include "ast/pointer_type.h"

using namespace haard;

PointerType::PointerType(Type* subtype) {
    set_kind(TYPE_POINTER);
    set_subtype(subtype);
}
