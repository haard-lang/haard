#ifndef HAARD_PRETTY_PRINTER_H
#define HAARD_PRETTY_PRINTER_H

#include <sstream>
#include "ast/ast.h"

namespace haard {
    class PrettyPrinter {
    public:
        PrettyPrinter();

    public:
        std::string get_output();

        void print_module(Module* module);
        void print_declaration(Declaration* decl);
        void print_import(Import* import);
        void print_function(Function* function);
        void print_function_parameters(Function* function);

        void print_statement(Statement* stmt);
        void print_compound_statement(CompoundStatement* stmt);
        void print_expression_statement(ExpressionStatement* stmt);

        void print_expression(Expression* expr);

        void print_cast_expression(Cast* expr);
        void print_not_in_expression(NotIn* expr);
        void print_index_expression(BinaryOperator* bin);
        void print_logical_not_expression(UnaryOperator* un);
        void print_binary_operator(BinaryOperator* bin, bool no_space=false);

        void print_unary_operator(UnaryOperator* un, bool last=false);

        void print_type(Type* type);
        void print_subtyped_type(SubtypedType* type);
        void print_tuple_type(TupleType* tuple);
        void print_function_type(FunctionType* type);
        void print_named_type(NamedType* type);
        void print_type_list(TypeList* tlist, const char* begin, const char* end);

        void print_identifier(Identifier* id);
        void print_generics(TypeList* g);

    private:
        void indent();
        void dedent();
        void print_indentation();

    private:
        int indent_level;
        std::stringstream out;
    };
}
#endif
