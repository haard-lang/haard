#include <iostream>
#include "token/token.h"
#include "scanner/scanner.h"
#include "parser/parser.h"
#include "string_pool/string_pool.h"

using namespace haard;

void test_parser(int argc, char** argv) {
    Parser p;

    auto m = p.read(argv[1]);
    delete m;
}

int main(int argc, char** argv) {
    test_parser(argc, argv);

    return 0;
}
