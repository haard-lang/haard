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
    function->set_generics(parse_generics());

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
    return parse_function_type();
}

Type* Parser::parse_function_type() {
    Type* type = parse_tuple_type();

    if (type->get_kind() == AST_TUPLE_TYPE) {
        TypeList* tlist = (TypeList*) type;

        if (match(TK_ARROW)) {
            tlist->add_type(parse_type());
            tlist->set_kind(AST_FUNCTION_TYPE);
        }

        type = tlist;
    }

    return type;
}

Type* Parser::parse_tuple_type() {
    TypeList* tuple;

    if (!lookahead(TK_LEFT_PARENTHESIS)) {
        return parse_primary_type();
    }

    expect(TK_LEFT_PARENTHESIS);
    tuple = parse_type_list(AST_TUPLE_TYPE);
    expect(TK_RIGHT_PARENTHESIS);

    return tuple;
}

Type* Parser::parse_primary_type() {
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
    } else if (match(TK_LEFT_SQUARE_BRACKET)) {
        type = parse_type();

        if (type == nullptr) {
            assert(false && "no type");
        } else {
            type = new SubtypedType(AST_LIST, type);
        }

        expect(TK_RIGHT_SQUARE_BRACKET);
    } else if (lookahead(TK_ID) || lookahead(TK_SCOPE)) {
        type = new NamedType(parse_identifier());
    }

    while (type != nullptr) {
        if (next_token_on_same_line() && match(TK_TIMES)) {
            type = new SubtypedType(AST_POINTER, type);
        } else if (next_token_on_same_line() && match(TK_POWER)) {
            type = new SubtypedType(AST_POINTER, type);
            type = new SubtypedType(AST_POINTER, type);
        } else if (next_token_on_same_line() && match(TK_BITWISE_AND)) {
            type = new SubtypedType(AST_REFERENCE, type);
        } else if (next_token_on_same_line() && match(TK_LOGICAL_AND)) {
            type = new SubtypedType(AST_REFERENCE, type);
            type = new SubtypedType(AST_REFERENCE, type);
        } else if (next_token_on_same_line() && match(TK_LEFT_SQUARE_BRACKET)) {
            /*type = new SubtypedType(AST_ARRAY, type);
            expect(TK_RIGHT_SQUARE_BRACKET);*/
        } else {
            break;
        }
    }

    return type;
}

Identifier* Parser::parse_identifier() {
    Token name;
    Token alias;
    bool alias_flag = false;
    bool global_flag = false;
    Identifier* id = nullptr;
    TypeList* generics = nullptr;

    if (match(TK_SCOPE)) {
        expect(TK_ID);
        name = matched;
        global_flag = true;
    } else if (match(TK_ID)) {
        if (lookahead(TK_SCOPE)) {
            alias = matched;
            expect(TK_SCOPE);
            expect(TK_ID);
            name = matched;
            alias_flag = true;
        } else {
            name = matched;
        }
    } else {
        assert(false && "invalid id");
    }

    generics = parse_generics();
    id = new Identifier(alias, name, alias_flag, global_flag, generics);

    return id;
}

TypeList* Parser::parse_generics() {
    TypeList* generics = nullptr;

    if (match(TK_BEGIN_TEMPLATE)) {
        generics = parse_type_list(AST_GENERICS);
        expect(TK_END_TEMPLATE);
    }

    return generics;
}

TypeList* Parser::parse_type_list(int kind) {
    TypeList* type_list = new TypeList(kind);
    Type* type = parse_type();

    if (type == nullptr) {
        assert(false && "type can't be null on function generics");
    }

    type_list->add_type(type);

    while (match(TK_COMMA)) {
        type = parse_type();

        if (type == nullptr) {
            assert(false && "type can't be null on function generics");
        }

        type_list->add_type(type);
    }

    return type_list;
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

bool Parser::match() {
    matched = tokens[idx];
    advance();

    return true;
}

bool Parser::expect(int kind) {
    if (match(kind)) {
        return true;
    }

    match();

    std::cout << "Expected a " << token_kind_to_str_map.at(kind)
              << " but got a " << token_kind_to_str_map.at(matched.get_kind())
              << std::endl;

    for (auto tk : tokens) {
        std::cout << tk.to_str() << '\n';
    }
    assert(false && "expected token");
}

bool Parser::has_next(int offset) {
    return idx + offset < tokens.size();
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

bool Parser::next_token_on_same_line() {
    if (has_next()) {
        return matched.get_line() == tokens[idx].get_line();
    }

    return false;
}

