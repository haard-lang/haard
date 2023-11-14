#ifndef HAARD_VARIABLE_H
#define HAARD_VARIABLE_H

#include "ast/declaration.h"
#include "ast/type.h"

namespace haard {
    class Variable : public Declaration {
    public:
        ~Variable();

    public:
        Type* get_type() const;
        void set_type(Type* newType);

    private:
        Type* type;
    };
}

#endif
