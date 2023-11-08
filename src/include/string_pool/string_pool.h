#ifndef HAARD_STRING_POOL_h
#define HAARD_STRING_POOL_h

#include <string>

namespace haard {
    class StringPool {
    public:
        static char* get(std::string value);
        static void dump();
    };
}

#endif
