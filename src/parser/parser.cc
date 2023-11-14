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
        } else if (lookahead(TK_DEF)) {
            module->add_function(parse_function());
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
    import->add_to_path(matched);

    while (match(TK_DOT)) {
        expect(TK_ID);
        import->add_to_path(matched);
    }

    if (match(TK_AS)) {
        expect(TK_ID);
        import->set_alias(matched);
    }

    return import;
}

Function* Parser::parse_function() {
    Function* function = new Function();

    expect(TK_DEF);
    expect(TK_ID);
    function->set_name(matched);

    expect(TK_COLON);
    indent();

    expect(TK_INT);

    if (has_parameters()) {
        parse_parameters(function);
    }

    dedent();

    return function;
}

void Parser::parse_parameters(Function* function) {
    Variable* param;

    while (has_parameters()) {
        expect(TK_AT);
        expect(TK_ID);
        param->set_name(matched);
        expect(TK_COLON);
        expect(TK_INT);

        function->add_parameter(param);
    }
}


void Parser::advance() {
    if (idx < tokens.size()) {
        ++idx;
    }
}

bool Parser::lookahead(int kind, int offset) {
    if (idx + offset < tokens.size()) {
        return tokens[idx + offset].get_kind() == kind;
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

void Parser::indent() {
    indent_stack.push(matched.get_whitespace());
}

void Parser::dedent() {
    indent_stack.pop();
}

bool Parser::has_parameters() {
    return lookahead(TK_AT) && lookahead(TK_ID, 1) && lookahead(TK_COLON, 2);
}
