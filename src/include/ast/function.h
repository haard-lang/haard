#ifndef HAARD_FUNCTION_H
#define HAARD_FUNCTION_H

#include <vector>
#include "ast/declaration.h"
#include "ast/variable.h"

namespace haard {
    class Function : public Declaration {
    public:
        Function();

        void add_parameter(Variable* param);
        int parameters_count();
        Variable* get_parameter(int idx);

    private:
        std::vector<Variable*> parameters;
    };
}
#endif
