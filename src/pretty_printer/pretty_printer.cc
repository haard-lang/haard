#include <cassert>
#include "pretty_printer/pretty_printer.h"

using namespace haard;

PrettyPrinter::PrettyPrinter() {
    indent_level = 0;
}

std::string PrettyPrinter::get_output() {
    return out.str();
}

void PrettyPrinter::print_module(Module* module) {
    /*for (int i = 0; i < module->imports_count(); ++i) {
        print_import(module->get_import(i));
        out << '\n';
    }*/

    for (int i = 0; i < module->declarations_count(); ++i) {
        print_declaration(module->get_declaration(i));
    }
}

void PrettyPrinter::print_declaration(Declaration* decl) {
    int kind = decl->get_kind();

    switch (kind) {
    case AST_IMPORT:
        print_import((Import*) decl);
        break;

    case AST_FUNCTION:
        print_function((Function*) decl);
        break;
    }

    out << '\n';
}

void PrettyPrinter::print_import(Import* import) {
    int i;

    out << "import ";

    for (i = 0; i < import->path_count() - 1; ++i) {
        out << import->get_path_token(i).get_value() << ".";
    }

    out << import->get_path_token(i).get_value();

    if (import->has_alias()) {
        out << " as " << import->get_alias().get_value();
    }
}

void PrettyPrinter::print_function(Function* function) {
    out << "def ";
    out << function->get_name().get_value();

    print_generics(function->get_generics());

    out << " : ";
    print_type(function->get_return_type());
    out << '\n';
    indent();

    print_function_parameters(function);
    print_statement(function->get_statements());

    dedent();
}

void PrettyPrinter::print_function_parameters(Function* function) {
    Variable* param;

    for (int i = 0; i < function->parameters_count(); ++i) {
        param = function->get_parameter(i);
        print_indentation();
        out << "@" << param->get_name().get_value() << " : ";
        print_type(param->get_type());
        out << "\n";
    }
}

void PrettyPrinter::print_statement(Statement* stmt) {
    switch (stmt->get_kind()) {
    case AST_COMPOUND_STATEMENT:
        print_compound_statement((CompoundStatement*) stmt);
        break;

    case AST_EXPRESSION_STATEMENT:
        print_expression_statement((ExpressionStatement*) stmt);
        break;

    default:
        assert(false && "invalid statement");
        break;
    }
}

void PrettyPrinter::print_compound_statement(CompoundStatement* stmt) {
    if (stmt->statements_count() == 0) {
        out << "pass";
        return;
    }

    for (int i = 0; i < stmt->statements_count(); ++i) {
        print_statement(stmt->get_statement(i));
    }
}

void PrettyPrinter::print_expression_statement(ExpressionStatement* stmt) {
    print_indentation();
    print_expression(stmt->get_expression());
    out << '\n';
}

void PrettyPrinter::print_expression(Expression* expr) {
    switch (expr->get_kind()) {
    case AST_ID:
        print_identifier((Identifier*) expr);
        break;

    case EXPR_ASSIGNMENT:
        print_binary_operator((BinaryOperator*) expr, "=");
        break;

    case EXPR_PLUS:
        print_binary_operator((BinaryOperator*) expr, "+");
        break;

    case EXPR_MINUS:
        print_binary_operator((BinaryOperator*) expr, "-");
        break;

    case EXPR_TIMES:
        print_binary_operator((BinaryOperator*) expr, "*");
        break;

    case EXPR_DIVISION:
        print_binary_operator((BinaryOperator*) expr, "/");
        break;

    case EXPR_MODULO:
        print_binary_operator((BinaryOperator*) expr, "%");
        break;

    case EXPR_INTEGER_DIVISION:
        print_binary_operator((BinaryOperator*) expr, "//");
        break;

    case EXPR_DOT:
        print_binary_operator((BinaryOperator*) expr, ".", true);
        break;

    case EXPR_ARROW:
        print_binary_operator((BinaryOperator*) expr, "->", true);
        break;

    case EXPR_INDEX:
        print_index_expression((BinaryOperator*) expr);
        break;

    case EXPR_UNARY_PLUS:
        print_unary_operator((UnaryOperator*) expr, "+");
        break;

    case EXPR_POS_INC:
        print_unary_operator((UnaryOperator*) expr, "++", true);
        break;

    case EXPR_POS_DEC:
        print_unary_operator((UnaryOperator*) expr, "--", true);
        break;
    }
}

void PrettyPrinter::print_index_expression(BinaryOperator* bin) {
    print_expression(bin->get_left());
    out << '[';

    print_expression(bin->get_right());
    out << ']';
}

void PrettyPrinter::print_binary_operator(BinaryOperator* bin, const char* oper, bool no_space) {
    out << "(";
    print_expression(bin->get_left());

    if (no_space) {
        out << oper;
    } else {
        out << ' ' << oper << ' ';
    }

    print_expression(bin->get_right());
    out << ")";
}

void PrettyPrinter::print_unary_operator(UnaryOperator* un, const char* oper, bool last) {
    out << "(";

    if (last) {
        print_expression(un->get_expression());
        out << oper;
    } else {
        out << oper;
        print_expression(un->get_expression());
    }

    out << ")";
}

void PrettyPrinter::print_type(Type* type) {
    if (type == nullptr) return;

    int kind = type->get_kind();

    switch (kind) {
    case TYPE_I8:
        out << "i8";
        break;

    case TYPE_U8:
        out << "u8";
        break;

    case TYPE_I16:
        out << "i16";
        break;

    case TYPE_U16:
        out << "u16";
        break;

    case TYPE_I32:
        out << "i32";
        break;

    case TYPE_U32:
        out << "u32";
        break;

    case TYPE_I64:
        out << "i64";
        break;

    case TYPE_U64:
        out << "u64";
        break;

    case TYPE_F32:
        out << "f32";
        break;

    case TYPE_F64:
        out << "f64";
        break;

    case TYPE_CHAR:
        out << "char";
        break;

    case TYPE_UCHAR:
        out << "uchar";
        break;

    case TYPE_SHORT:
        out << "short";
        break;

    case TYPE_USHORT:
        out << "ushort";
        break;

    case TYPE_INT:
        out << "int";
        break;

    case TYPE_UINT:
        out << "uint";
        break;

    case TYPE_LONG:
        out << "long";
        break;

    case TYPE_ULONG:
        out << "ulong";
        break;

    case TYPE_FLOAT:
        out << "float";
        break;

    case TYPE_DOUBLE:
        out << "double";
        break;

    case TYPE_VOID:
        out << "void";
        break;

    case TYPE_STR:
        out << "str";
        break;

    case TYPE_SYMBOL:
        out << "sym";
        break;

    case TYPE_BOOL:
        out << "bool";
        break;

    case TYPE_POINTER:
    case TYPE_REFERENCE:
    case TYPE_LIST:
        print_subtyped_type((SubtypedType*) type);
        break;

    case TYPE_TUPLE:
        print_tuple_type((TupleType*) type);
        break;

    case TYPE_FUNCTION:
        print_function_type((FunctionType*) type);
        break;

    case TYPE_NAMED:
        print_named_type((NamedType*) type);
        break;
    }
}

void PrettyPrinter::print_subtyped_type(SubtypedType* type) {
    int kind = type->get_kind();

    switch (kind) {
    case TYPE_POINTER:
        print_type(type->get_subtype());
        out << '*';
        break;

    case TYPE_REFERENCE:
        print_type(type->get_subtype());
        out << '&';
        break;

    case TYPE_LIST:
        out << '[';
        print_type(type->get_subtype());
        out << ']';
        break;
    }
}

void PrettyPrinter::print_tuple_type(TupleType* tuple) {
    print_type_list(tuple->get_types(), "(", ")");
}

void PrettyPrinter::print_function_type(FunctionType* type) {
    print_type_list(type->get_param_types(), "(", ")");
    out << " -> ";
    print_type(type->get_return_type());
}

void PrettyPrinter::print_named_type(NamedType* type) {
    print_identifier(type->get_identifier());
}

void PrettyPrinter::print_type_list(TypeList* tlist, const char* begin, const char* end) {
    if (tlist == nullptr) {
        return;
    }

    int i;

    out << begin;

    for (i = 0; i < tlist->types_count() - 1; ++i) {
        print_type(tlist->get_type(i));
        out << ", ";
    }

    print_type(tlist->get_type(i));
    out << end;
}

void PrettyPrinter::print_identifier(Identifier* id) {
    if (id->has_global_alias()) {
        out << "::";
    } else if (id->has_alias()) {
        out << id->get_alias().get_value();
        out << "::";
    }

    out << id->get_name().get_value();
    print_generics(id->get_generics());
}

void PrettyPrinter::print_generics(TypeList* g) {
    print_type_list(g, "<", ">");
}

void PrettyPrinter::indent() {
    ++indent_level;
}

void PrettyPrinter::dedent() {
    --indent_level;
}

void PrettyPrinter::print_indentation() {
    for (int i = 0; i < indent_level; ++i) {
        out << "    ";
    }
}
