#ifndef HAARD_FUNCTION_H
#define HAARD_FUNCTION_H

#include <vector>
#include "ast/declaration.h"
#include "ast/variable.h"
#include "ast/type.h"

namespace haard {
    class Function : public Declaration {
    public:
        Function();
        ~Function();

        void add_parameter(Variable* param);
        int parameters_count();
        Variable* get_parameter(int idx);

        Type* get_return_type() const;
        void set_return_type(Type *newReturn_type);

    private:
        Type* return_type;
        std::vector<Variable*> parameters;
    };
}
#endif
