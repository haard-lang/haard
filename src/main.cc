#include <iostream>
#include "token/token.h"
#include "scanner/scanner.h"
#include "parser/parser.h"
#include "string_pool/string_pool.h"
#include "pretty_printer/pretty_printer.h"

using namespace haard;

void test_parser(int argc, char** argv) {
    Parser p;

    auto m = p.read(argv[1]);
    delete m;
}

void test_pretty_printer(int argc, char** argv) {
    Parser parser;
    PrettyPrinter printer;

    Module* module = parser.read(argv[1]);
    printer.print_module(module);
    std::cout << printer.get_output() << '\n';

    delete module;
}

int main(int argc, char** argv) {
    test_pretty_printer(argc, argv);

    return 0;
}
