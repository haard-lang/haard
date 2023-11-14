#ifndef HAARD_MODULE_H
#define HAARD_MODULE_H

#include <vector>
#include "ast/declaration.h"

namespace haard {
    class Module {
    private:
        std::vector<Declaration*> decls;
    };
}

#endif
