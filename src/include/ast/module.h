#ifndef HAARD_MODULE_H
#define HAARD_MODULE_H

#include <vector>
#include "ast/declaration.h"
#include "ast/import.h"

namespace haard {
    class Module {
    public:
        ~Module();

    public:
        void add_import(Import* import);

    private:
        std::vector<Import*> imports;
        std::vector<Declaration*> decls;
    };
}

#endif
