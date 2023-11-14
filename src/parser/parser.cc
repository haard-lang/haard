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

    Type* return_type = parse_type();

    if (return_type) {
        function->set_return_type(return_type);
    } else {
        assert(false && "Expected return type");
    }

    if (has_parameters()) {
        parse_parameters(function);
    }

    dedent();

    return function;
}

void Parser::parse_parameters(Function* function) {
    Variable* param;

    while (has_parameters()) {
        param = new Variable();

        expect(TK_AT);
        expect(TK_ID);
        param->set_name(matched);

        expect(TK_COLON);
        Type* type = parse_type();

        if (type != nullptr) {
            param->set_type(type);
        } else {
            assert(false && "expected type in parameter");
        }

        function->add_parameter(param);
    }
}

Type* Parser::parse_type() {
    Type* type = nullptr;

    if (match(TK_INT)) {
       type = new Type(AST_INT, matched);
    } else if (match(TK_UINT)) {
       type = new Type(AST_UINT, matched);
    } else if (match(TK_FLOAT)) {
       type = new Type(AST_FLOAT, matched);
    } else if (match(TK_DOUBLE)) {
       type = new Type(AST_DOUBLE, matched);
    } else if (match(TK_SHORT)) {
       type = new Type(AST_SHORT, matched);
    } else if (match(TK_USHORT)) {
       type = new Type(AST_USHORT, matched);
    } else if (match(TK_LONG)) {
       type = new Type(AST_LONG, matched);
    } else if (match(TK_ULONG)) {
       type = new Type(AST_ULONG, matched);
    } else if (match(TK_CHAR)) {
       type = new Type(AST_CHAR, matched);
    } else if (match(TK_UCHAR)) {
       type = new Type(AST_UCHAR, matched);
    } else if (match(TK_SYMBOL)) {
       type = new Type(AST_SYMBOL, matched);
    } else if (match(TK_VOID)) {
       type = new Type(AST_VOID, matched);
    } else if (match(TK_BOOL)) {
       type = new Type(AST_BOOL, matched);
    } else if (match(TK_STR)) {
       type = new Type(AST_STR, matched);
    } else if (match(TK_I8)) {
       type = new Type(AST_I8, matched);
    } else if (match(TK_I16)) {
       type = new Type(AST_I16, matched);
    } else if (match(TK_I32)) {
       type = new Type(AST_I32, matched);
    } else if (match(TK_I64)) {
       type = new Type(AST_I64, matched);
    } else if (match(TK_U8)) {
       type = new Type(AST_U8, matched);
    } else if (match(TK_U16)) {
       type = new Type(AST_U16, matched);
    } else if (match(TK_U32)) {
       type = new Type(AST_U32, matched);
    } else if (match(TK_U64)) {
       type = new Type(AST_U64, matched);
    } else if (match(TK_F32)) {
       type = new Type(AST_F32, matched);
    } else if (match(TK_F64)) {
       type = new Type(AST_F64, matched);
    }

    return type;
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
