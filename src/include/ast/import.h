#ifndef HAARD_IMPORT_H
#define HAARD_IMPORT_H

#include <vector>
#include "token/token.h"

namespace haard {
    class Import {
    public:

    private:
        std::vector<Token> path;
        Token alias;
    };
}

#endif
