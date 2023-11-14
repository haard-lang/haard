#include "ast/variable.h"

using namespace haard;

Variable::~Variable() {

}

Type* Variable::get_type() const {
    return type;
}

void Variable::set_type(Type* newType) {
    type = newType;
}
