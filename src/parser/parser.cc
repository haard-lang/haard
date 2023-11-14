#include <iostream>
#include "parser/parser.h"
#include "scanner/scanner.h"

using namespace haard;

Module* Parser::read(std::string path) {
    Scanner sc;

    tokens = sc.read(path);

    for (auto tk : tokens) {
        std::cout << tk.to_str() << '\n';
    }
}
