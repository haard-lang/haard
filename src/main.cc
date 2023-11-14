#include <iostream>
#include "token/token.h"
#include "scanner/scanner.h"
#include "parser/parser.h"
#include "string_pool/string_pool.h"

using namespace haard;

void test_parser(int argc, char** argv) {
    Parser p;

    p.read(argv[1]);
}

int main(int argc, char** argv) {
    test_parser(argc, argv);

    return 0;
}
