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

    function->set_statements(parse_compound_statement());
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

Statement* Parser::parse_statement() {
    Statement* stmt = nullptr;

    /*if (lookahead(TK_WHILE)) {
        stmt = parse_while_statement();
    } else if (lookahead(TK_FOR)) {
        stmt = parse_for_statement();
    } else if (lookahead(TK_IF)) {
        stmt = parse_if_statement();
    } else if (lookahead(TK_RETURN)) {
        stmt = parse_jump_statement(TK_RETURN, STMT_RETURN);
    } else if (lookahead(TK_YIELD)) {
        stmt = parse_jump_statement(TK_YIELD, STMT_YIELD);
    } else if (lookahead(TK_CONTINUE)) {
        stmt = parse_jump_statement(TK_CONTINUE, STMT_CONTINUE);
    } else if (lookahead(TK_GOTO)) {
        stmt = parse_jump_statement(TK_GOTO, STMT_GOTO);
    } else if (lookahead(TK_BREAK)) {
        stmt = parse_jump_statement(TK_BREAK, STMT_BREAK);
    } else if (lookahead(TK_VAR)) {
        stmt = parse_variable_declaration();*/
    //} else {
        stmt = new ExpressionStatement(parse_expression());
    //}

    return stmt;
}

CompoundStatement* Parser::parse_compound_statement() {
    CompoundStatement* statements = new CompoundStatement();

    if (match(TK_PASS)) {
        return statements;
    }

    while (is_indented() && !lookahead(TK_RIGHT_CURLY_BRACKET)) {
        statements->add_statement(parse_statement());
    }

    return statements;
}

Type* Parser::parse_type() {
    return parse_tuple_or_function_type();
}

Type* Parser::parse_tuple_or_function_type() {
    Type* type;
    TypeList* types;

    if (!lookahead(TK_LEFT_PARENTHESIS)) {
        return parse_primary_type();
    }

    expect(TK_LEFT_PARENTHESIS);
    types = parse_type_list(TYPE_TUPLE);
    expect(TK_RIGHT_PARENTHESIS);

    if (match(TK_ARROW)) {
        if (!next_token_on_same_line()) {
            assert(false && "return type should be on same line");
        }

        type = parse_type();

        if (type == nullptr) {
            assert(false && "expected return type");
        }

        type = new FunctionType(types, type);
    } else {
        type = new TupleType(types);
    }

    return type;
}

Type* Parser::parse_primary_type() {
    Type* type = nullptr;

    if (match(TK_INT)) {
       type = new Type(TYPE_INT, matched);
    } else if (match(TK_UINT)) {
       type = new Type(TYPE_UINT, matched);
    } else if (match(TK_FLOAT)) {
       type = new Type(TYPE_FLOAT, matched);
    } else if (match(TK_DOUBLE)) {
       type = new Type(TYPE_DOUBLE, matched);
    } else if (match(TK_SHORT)) {
       type = new Type(TYPE_SHORT, matched);
    } else if (match(TK_USHORT)) {
       type = new Type(TYPE_USHORT, matched);
    } else if (match(TK_LONG)) {
       type = new Type(TYPE_LONG, matched);
    } else if (match(TK_ULONG)) {
       type = new Type(TYPE_ULONG, matched);
    } else if (match(TK_CHAR)) {
       type = new Type(TYPE_CHAR, matched);
    } else if (match(TK_UCHAR)) {
       type = new Type(TYPE_UCHAR, matched);
    } else if (match(TK_SYMBOL)) {
       type = new Type(TYPE_SYMBOL, matched);
    } else if (match(TK_VOID)) {
       type = new Type(TYPE_VOID, matched);
    } else if (match(TK_BOOL)) {
       type = new Type(TYPE_BOOL, matched);
    } else if (match(TK_STR)) {
       type = new Type(TYPE_STR, matched);
    } else if (match(TK_I8)) {
       type = new Type(TYPE_I8, matched);
    } else if (match(TK_I16)) {
       type = new Type(TYPE_I16, matched);
    } else if (match(TK_I32)) {
       type = new Type(TYPE_I32, matched);
    } else if (match(TK_I64)) {
       type = new Type(TYPE_I64, matched);
    } else if (match(TK_U8)) {
       type = new Type(TYPE_U8, matched);
    } else if (match(TK_U16)) {
       type = new Type(TYPE_U16, matched);
    } else if (match(TK_U32)) {
       type = new Type(TYPE_U32, matched);
    } else if (match(TK_U64)) {
       type = new Type(TYPE_U64, matched);
    } else if (match(TK_F32)) {
       type = new Type(TYPE_F32, matched);
    } else if (match(TK_F64)) {
       type = new Type(TYPE_F64, matched);
    } else if (match(TK_LEFT_SQUARE_BRACKET)) {
        type = parse_type();

        if (type == nullptr) {
            assert(false && "no type");
        } else {
            type = new ListType(type);
        }

        expect(TK_RIGHT_SQUARE_BRACKET);
    } else if (lookahead(TK_ID) || lookahead(TK_SCOPE)) {
        type = new NamedType(parse_identifier());
    }

    while (type != nullptr) {
        if (match_same_line(TK_TIMES)) {
            type = new PointerType(type);
        } else if (match_same_line(TK_POWER)) {
            type = new PointerType(type);
            type = new PointerType(type);
        } else if (match_same_line(TK_BITWISE_AND)) {
            type = new ReferenceType(type);
        } else if (match_same_line(TK_LOGICAL_AND)) {
            type = new ReferenceType(type);
            type = new ReferenceType(type);
        } else if (match_same_line(TK_LEFT_SQUARE_BRACKET)) {
            type = new ArrayType(type, parse_expression());
            expect(TK_RIGHT_SQUARE_BRACKET);
        } else {
            break;
        }
    }

    return type;
}

Expression* Parser::parse_expression() {
    return parse_assignment_expression();
}

Expression* Parser::parse_assignment_expression() {
    Token oper;
    Expression* expr = parse_cast_expression();

    while (true) {
        if (match(TK_ASSIGNMENT)) {
            oper = matched;
            expr = new Assignment(oper, expr, parse_cast_expression());
        } else if (match(TK_BITWISE_AND_ASSIGNMENT)) {
            oper = matched;
            expr = new BitwiseAndAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_BITWISE_XOR_ASSIGNMENT)) {
            oper = matched;
            expr = new BitwiseXorAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_BITWISE_OR_ASSIGNMENT)) {
            oper = matched;
            expr = new BitwiseOrAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_BITWISE_NOT_ASSIGNMENT)) {
            oper = matched;
            expr = new BitwiseNotAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_DIVISION_ASSIGNMENT)) {
            oper = matched;
            expr = new DivisionAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_INTEGER_DIVISION_ASSIGNMENT)) {
            oper = matched;
            expr = new IntegerDivisionAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_MINUS_ASSIGNMENT)) {
            oper = matched;
            expr = new MinusAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_MODULO_ASSIGNMENT)) {
            oper = matched;
            expr = new ModuloAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_PLUS_ASSIGNMENT)) {
            oper = matched;
            expr = new PlusAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_TIMES_ASSIGNMENT)) {
            oper = matched;
            expr = new TimesAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_SLL_ASSIGNMENT)) {
            oper = matched;
            expr = new ShiftLeftLogicalAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_SRA_ASSIGNMENT)) {
            oper = matched;
            expr = new ShiftRightArithmeticAssignment(oper, expr, parse_cast_expression());
        } else if (match(TK_SRL_ASSIGNMENT)) {
            oper = matched;
            expr = new ShiftRightLogicalAssignment(oper, expr, parse_cast_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_cast_expression() {
    Token oper;
    Type* type = nullptr;
    Expression* expr = parse_logical_or_expression();

    if (match(TK_AS)) {
        oper = matched;

        if (next_token_on_same_line()) {
            type = parse_type();
        }

        if (type == nullptr) {
            assert(false && "missing type on cast expression");
        }

        expr = new Cast(oper, expr, type);
    }

    return expr;
}

Expression* Parser::parse_logical_or_expression() {
    Token oper;
    Expression* expr = parse_logical_and_expression();

    while (true) {
        if (match(TK_OR) || match(TK_LOGICAL_OR)) {
            oper = matched;
            expr = new LogicalOr(oper, expr, parse_logical_and_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_logical_and_expression() {
    Token oper;
    Expression* expr = parse_equality_expression();

    while (true) {
        if (match(TK_AND) || match(TK_LOGICAL_AND)) {
            oper = matched;
            expr = new LogicalAnd(oper, expr, parse_equality_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_equality_expression() {
    Token oper;
    Expression* expr = parse_relational_expression();

    while (true) {
        if (match(TK_EQ)) {
            oper = matched;
            expr = new Equal(oper, expr, parse_relational_expression());
        } else if (match(TK_NE)) {
            oper = matched;
            expr = new NotEqual(oper, expr, parse_relational_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_relational_expression() {
    Token oper;
    Expression* expr = parse_range_expression();

    while (true) {
        if (match(TK_LT)) {
            oper = matched;
            expr = new LessThan(oper, expr, parse_range_expression());
        } else if (match(TK_GT)) {
            oper = matched;
            expr = new GreaterThan(oper, expr, parse_range_expression());
        } else if (match(TK_LE)) {
            oper = matched;
            expr = new LessThanOrEqual(oper, expr, parse_range_expression());
        } else if (match(TK_GE)) {
            oper = matched;
            expr = new GreaterThanOrEqual(oper, expr, parse_range_expression());
        } else if (match(TK_IN)) {
            oper = matched;
            expr = new In(oper, expr, parse_range_expression());
        } else if (match(TK_NOT)) {
            oper = matched;
            expect(TK_IN);
            expr = new NotIn(oper, expr, parse_range_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_range_expression() {
    Token oper;
    Expression* expr = parse_arith_expression();

    while (true) {
        if (match(TK_INCLUSIVE_RANGE)) {
            oper = matched;
            expr = new InclusiveRange(oper, expr, parse_arith_expression());
        } else if (match(TK_EXCLUSIVE_RANGE)) {
            oper = matched;
            expr = new ExclusiveRange(oper, expr, parse_arith_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_arith_expression() {
    Token oper;
    Expression* expr = parse_term_expression();

    while (true) {
        if (match_same_line(TK_PLUS)) {
            oper = matched;
            expr = new Plus(oper, expr, parse_term_expression());
        } else if (match_same_line(TK_MINUS)) {
            oper = matched;
            expr = new Minus(oper, expr, parse_term_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_term_expression() {
    Token oper;
    Expression* expr = parse_power_expression();

    while (true) {
        if (match_same_line(TK_TIMES)) {
            oper = matched;
            expr = new Times(oper, expr, parse_power_expression());
        } else if (match_same_line(TK_DIVISION)) {
            oper = matched;
            expr = new Division(oper, expr, parse_power_expression());
        } else if (match_same_line(TK_MODULO)) {
            oper = matched;
            expr = new Modulo(oper, expr, parse_power_expression());
        } else if (match_same_line(TK_INTEGER_DIVISION)) {
            oper = matched;
            expr = new IntegerDivision(oper, expr, parse_power_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_power_expression() {
    Token oper;
    Expression* expr = parse_bitwise_or_expression();

    while (true) {
        if (match(TK_POWER)) {
            oper = matched;
            expr = new Power(oper, expr, parse_bitwise_or_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_bitwise_or_expression() {
    Token oper;
    Expression* expr = parse_bitwise_xor_expression();

    while (true) {
        if (match(TK_BITWISE_OR)) {
            oper = matched;
            expr = new BitwiseOr(oper, expr, parse_bitwise_xor_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_bitwise_xor_expression() {
    Token oper;
    Expression* expr = parse_bitwise_and_expression();

    while (true) {
        if (match(TK_BITWISE_XOR)) {
            oper = matched;
            expr = new BitwiseXor(oper, expr, parse_bitwise_and_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_bitwise_and_expression() {
    Token oper;
    Expression* expr = parse_shift_expression();

    while (true) {
        if (match(TK_BITWISE_AND)) {
            oper = matched;
            expr = new BitwiseAnd(oper, expr, parse_shift_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_shift_expression() {
    Token oper;
    Expression* expr = parse_unary_expression();

    while (true) {
        if (match(TK_SLL)) {
            oper = matched;
            expr = new ShiftLeftLogical(oper, expr, parse_unary_expression());
        } else if (match(TK_SRL)) {
            oper = matched;
            expr = new ShiftRightLogical(oper, expr, parse_unary_expression());
        } else if (match(TK_SRA)) {
            oper = matched;
            expr = new ShiftRightArithmetic(oper, expr, parse_unary_expression());
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_unary_expression() {
    Token oper;
    Expression* expr = nullptr;

    if (match(TK_LOGICAL_NOT) || match(TK_NOT)) {
        oper = matched;
        expr = new LogicalNot(oper, parse_unary_expression());
    } else if (match(TK_BITWISE_AND)) {
        oper = matched;
        expr = new AddressOf(oper, parse_unary_expression());
    } else if (match(TK_TIMES)) {
        oper = matched;
        expr = new Dereference(oper, parse_unary_expression());
    } else if (match(TK_POWER)) {
        oper = matched;
        expr = new Dereference(oper, parse_unary_expression());
        expr = new Dereference(oper, expr);
    } else if (match(TK_BITWISE_NOT)) {
        oper = matched;
        expr = new BitwiseNot(oper, parse_unary_expression());
    } else if (match(TK_MINUS)) {
        oper = matched;
        expr = new UnaryMinus(oper, parse_unary_expression());
    } else if (match(TK_PLUS)) {
        oper = matched;
        expr = new UnaryPlus(oper, parse_unary_expression());
    } else if (match(TK_INC)) {
        oper = matched;
        expr = new PreIncrement(oper, parse_unary_expression());
    } else if (match(TK_DEC)) {
        oper = matched;
        expr = new PreDecrement(oper, parse_unary_expression());
    } else if (match(TK_SIZEOF)) {
        oper = matched;
        expect(TK_LEFT_PARENTHESIS);
        expr = new Sizeof(oper, parse_expression());
        expect(TK_RIGHT_PARENTHESIS);
    } else if (lookahead(TK_NEW)) {
        expr = parse_new_expression();
    } else if (lookahead(TK_DELETE)) {
        expr = parse_delete_expression();
    } else {
        expr = parse_postfix_expression();
    }

    return expr;
}

Expression* Parser::parse_postfix_expression() {
    Token oper;
    Expression* expr = parse_primary_expression();

    while (true) {
        if (match(TK_DOT)) {
            oper = matched;
            expr = new BinaryOperator(EXPR_DOT, oper, expr, parse_identifier());
        } else if (match(TK_ARROW)) {
            oper = matched;
            expr = new BinaryOperator(EXPR_ARROW, oper, expr, parse_identifier());
        } else if (match(TK_LEFT_SQUARE_BRACKET)) {
            oper = matched;
            expr = new BinaryOperator(EXPR_INDEX, oper, expr, parse_expression());
            expect(TK_RIGHT_SQUARE_BRACKET);
        } else if (match_same_line(TK_LEFT_PARENTHESIS)) {
            oper = matched;
            expr = new Call(oper, expr, parse_argument_list());
            expect(TK_RIGHT_PARENTHESIS);
        } else if (match_same_line(TK_INC)) {
            oper = matched;
            expr = new UnaryOperator(EXPR_POS_INCREMENT, oper, expr);
        } else if (match_same_line(TK_DEC)) {
            oper = matched;
            expr = new UnaryOperator(EXPR_POS_DECREMENT, oper, expr);
        } else {
            break;
        }
    }

    return expr;
}

Expression* Parser::parse_primary_expression() {
    Expression* expr = nullptr;

    if (lookahead(TK_ID) || lookahead(TK_SCOPE)) {
        expr = parse_identifier();
    } else if (match(TK_LITERAL_INTEGER)) {
        expr = new IntegerLiteral(matched);
    } else if (match(TK_LITERAL_FLOAT)) {
        expr = new FloatLiteral(matched);
    }

    return expr;
}

Expression* Parser::parse_delete_expression() {
    Token oper;
    Expression* expr = nullptr;

    expect(TK_DELETE);
    oper = matched;

    if (match(TK_LEFT_SQUARE_BRACKET)) {
        expect(TK_RIGHT_SQUARE_BRACKET);
        expr = new DeleteArray(oper, parse_expression());
    } else {
        expr = new Delete(oper, parse_expression());
    }

    return expr;
}

ExpressionList* Parser::parse_argument_list() {
    ExpressionList* arguments = new ExpressionList();

    if (!lookahead(TK_RIGHT_PARENTHESIS)) {
        arguments->add_expression(parse_expression());

        while (match(TK_COMMA)) {
            arguments->add_expression(parse_expression());
        }
    }

    return arguments;
}

Expression* Parser::parse_new_expression() {
    Type* type;
    New* expr = new New();

    expect(TK_NEW);
    expr->set_token(matched);

    type = parse_type();

    if (type == nullptr) {
        assert(false && "missing type on new");
    }

    expr->set_type(type);

    if (match(TK_LEFT_PARENTHESIS)) {
        expr->set_arguments(parse_argument_list());
        expect(TK_RIGHT_PARENTHESIS);
    }

    return expr;
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
        match();
        std::cout << matched.to_str() << '\n';
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

bool Parser::match_same_line(int kind) {
    return next_token_on_same_line() && match(kind);
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

bool Parser::is_indented() {
    if (has_next()) {
        return tokens[idx].get_whitespace() > indent_stack.top();
    }

    return false;
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
