#include "pretty_printer/pretty_printer.h"

using namespace haard;

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
    out << " : int\n";

    for (int i = 0; i < function->parameters_count(); ++i) {
        Variable* param = function->get_parameter(i);
        out << "@" << param->get_name().get_value() << " : int\n";
    }
}
