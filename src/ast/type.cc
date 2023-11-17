#include <set>
#include "ast/type.h"
#include "type_pool/type_pool.h"

using namespace haard;

TypePool type_pool;

Type::Type() {
    type_pool.add_type(this);
}

Type::~Type() {

}

Type::Type(int kind, const Token& token) {
    set_kind(kind);
    set_token(token);
    type_pool.add_type(this);
}
