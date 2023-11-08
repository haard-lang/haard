#include <set>
#include <iostream>
#include "string_pool/string_pool.h"

using namespace haard;

std::set<std::string> string_pool_set;

char* StringPool::get(std::string value) {
    auto v = string_pool_set.insert(value);

    if (v.second) {
        return (char*) v.first->c_str();
    }

    return nullptr;
}

void StringPool::dump() {
    for (auto it = string_pool_set.begin(); it != string_pool_set.end(); ++it) {
        std::cout << *it << ", ";
    }

    std::cout << '\n';
}
