#include <iostream>
#include "parser/parser.h"
#include "scanner/scanner.h"
#include <cassert>

using namespace haard;

Parser::Parser() {
    idx = 0;
}

Module* Parser::read(std::string path) {
    Module* module;
    Scanner sc;

    idx = 0;
    tokens = sc.read(path);
    module = parse_module();

    return module;
}

Module* Parser::parse_module() {
    Module* module = new Module();

    while (true) {
        if (lookahead(TK_IMPORT)) {
            module->add_import(parse_import());
        } else {
            break;
        }
    }

    return module;
}

Import* Parser::parse_import() {
    Import* import = new Import();

    expect(TK_IMPORT);

    expect(TK_ID);

    while (match(TK_DOT)) {
        expect(TK_ID);
    }

    if (match(TK_AS)) {
        expect(TK_ID);
    }

    return import;
}

void Parser::advance() {
    if (idx < tokens.size()) {
        ++idx;
    }
}

bool Parser::lookahead(int kind) {
    if (idx < tokens.size()) {
        return tokens[idx].get_kind() == kind;
    }

    return false;
}

bool Parser::match(int kind) {
    if (lookahead(kind)) {
        matched = tokens[idx];
        advance();
        return true;
    }

    return false;
}

bool Parser::expect(int kind) {
    if (match(kind)) {
        return true;
    }

    assert(false && "expected token");
}
