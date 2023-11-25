#ifndef HAARD_TUPLE_TYPE_H
#define HAARD_TUPLE_TYPE_H

#include "ast/type.h"
#include "ast/type_list.h"

namespace haard {
    class TupleType : public Type {
    public:
        TupleType(TypeList* types);

        TypeList* get_types() const;
        void set_types(TypeList* newTypes);

    private:
        TypeList* types;
    };
}

#endif
