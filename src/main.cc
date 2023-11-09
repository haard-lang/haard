#include <iostream>
#include "token/token.h"
#include "scanner/scanner.h"
#include "string_pool/string_pool.h"

using namespace haard;

int main(int argc, char** argv) {
    Scanner sc;
    auto tokens = sc.read(argv[1]);

    for (int i = 0; i < tokens.size(); ++i) {
        std::cout  << tokens[i].to_str() << "\n";
    }

    return 0;
}
