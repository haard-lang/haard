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

void PrettyPrinter::print_type(Type* type) {
    if (type == nullptr) return;

    int kind = type->get_kind();

    switch (kind) {
    case AST_I8:
        out << "i8";
        break;

    case AST_U8:
        out << "u8";
        break;

    case AST_I16:
        out << "i16";
        break;

    case AST_U16:
        out << "u16";
        break;

    case AST_I32:
        out << "i32";
        break;

    case AST_U32:
        out << "u32";
        break;

    case AST_I64:
        out << "i64";
        break;

    case AST_U64:
        out << "u64";
        break;

    case AST_F32:
        out << "f32";
        break;

    case AST_F64:
        out << "f64";
        break;

    case AST_CHAR:
        out << "char";
        break;

    case AST_UCHAR:
        out << "uchar";
        break;

    case AST_SHORT:
        out << "short";
        break;

    case AST_USHORT:
        out << "ushort";
        break;

    case AST_INT:
        out << "int";
        break;

    case AST_UINT:
        out << "uint";
        break;

    case AST_LONG:
        out << "long";
        break;

    case AST_ULONG:
        out << "ulong";
        break;

    case AST_FLOAT:
        out << "float";
        break;

    case AST_DOUBLE:
        out << "double";
        break;

    case AST_VOID:
        out << "void";
        break;

    case AST_STR:
        out << "str";
        break;

    case AST_SYMBOL:
        out << "sym";
        break;

    case AST_BOOL:
        out << "bool";
        break;

    case AST_POINTER:
    case AST_REFERENCE:
    case AST_LIST:
        print_subtyped_type((SubtypedType*) type);
        break;

    case AST_TUPLE_TYPE:
        print_tuple_type((TypeList*) type);
        break;

    case AST_FUNCTION_TYPE:
        print_function_type((TypeList*) type);
        break;

    case AST_NAMED:
        print_named_type((NamedType*) type);
        break;
    }
}

void PrettyPrinter::print_subtyped_type(SubtypedType* type) {
    int kind = type->get_kind();

    switch (kind) {
    case AST_POINTER:
        print_type(type->get_subtype());
        out << '*';
        break;

    case AST_REFERENCE:
        print_type(type->get_subtype());
        out << '&';
        break;

    case AST_LIST:
        out << '[';
        print_type(type->get_subtype());
        out << ']';
        break;
    }
}

void PrettyPrinter::print_tuple_type(TypeList* tuple) {
    print_type_list(tuple, "(", ")");
}

void PrettyPrinter::print_function_type(TypeList* type) {
    print_type_list(type, "(", ")", true);
    out << " -> ";
    print_type(type->get_type(type->types_count() - 1));
}

void PrettyPrinter::print_named_type(NamedType* type) {
    print_identifier(type->get_identifier());
}

void PrettyPrinter::print_type_list(TypeList* tlist, const char* begin, const char* end, bool last) {
    if (tlist == nullptr) {
        return;
    }

    int i;
    int end_idx = tlist->types_count() - 1;

    out << begin;

    if (last) {
        --end_idx;
    }

    for (i = 0; i < end_idx; ++i) {
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
