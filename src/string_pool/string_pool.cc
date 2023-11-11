#include <set>
#include <iostream>
#include "string_pool/string_pool.h"

using namespace haard;

std::set<std::string> string_pool_set;

const char* StringPool::get(std::string value) {
    auto v = string_pool_set.insert(value);

    return v.first->c_str();
}

void StringPool::dump() {
    for (auto it : string_pool_set) {
        std::cout << it << ", ";
    }

    std::cout << '\n';
}
