#include "type_pool/type_pool.h"

using namespace haard;

TypePool::~TypePool() {
    for (auto t : types) {
        delete t;
    }
}

void TypePool::add_type(Type* type) {
    types.push_back(type);
}
