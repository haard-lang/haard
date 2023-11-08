#ifndef HAARD_SCANNER_H
#define HAARD_SCANNER_H

#include <string>

namespace haard {
    class Scanner {
    public:
        void read(std::string path);

    private:
        void read_to_buffer(std::string path);

    private:
        std::string buffer;
    };
}
#endif
