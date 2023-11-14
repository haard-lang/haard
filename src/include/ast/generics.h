#ifndef HAARD_GENERICS_H
#define HAARD_GENERICS_H

#include <vector>
#include "ast/type.h"

namespace haard {
    class Generics {
    public:
        void add_type(Type* type);
        Type* get_type(int idx);
        int types_count();

    private:
        std::vector<Type*> types;
    };
}

#endif
