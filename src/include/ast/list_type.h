#ifndef HAARD_LIST_TYPE_H
#define HAARD_LIST_TYPE_H

#include "ast/subtyped_type.h"

namespace haard {
    class ListType : public SubtypedType {
    public:
        ListType(Type* subtype);
    };
}

#endif
