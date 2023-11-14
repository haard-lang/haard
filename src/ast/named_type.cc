#include "ast/named_type.h"

using namespace haard;

NamedType::NamedType(Identifier* id) {
    set_kind(AST_NAMED);
    set_identifier(id);
}

NamedType::~NamedType() {
    delete identifier;
}

Identifier* NamedType::get_identifier() const {
    return identifier;
}

void NamedType::set_identifier(Identifier* newIdentifier) {
    identifier = newIdentifier;
}
