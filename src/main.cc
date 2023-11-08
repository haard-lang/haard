#include <iostream>
#include "token/token.h"
#include "scanner/scanner.h"
#include "string_pool/string_pool.h"

using namespace haard;

int main(int argc, char** argv) {
    Token token;
    Scanner sc;
    sc.read(argv[1]);

    return 0;
}
