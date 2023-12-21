#ifndef HAARD_PARSER_H
#define HAARD_PARSER_H

#include <string>
#include <vector>
#include <stack>
#include "ast/ast.h"
#include "token/token.h"

namespace haard {
    class Parser {
    public:
        Parser();

    public:
        Module* read(std::string path);

    public:
        Module* parse_module();
        Import* parse_import();

        Function* parse_function();
        void parse_parameters(Function* function);

        Statement* parse_statement();
        WhileStatement* parse_while_statement();
        CompoundStatement* parse_compound_statement();

        Type* parse_type();
        Type* parse_function_type();
        Type* parse_tuple_or_function_type();
        Type* parse_primary_type();

        Expression* parse_expression();
        Expression* parse_assignment_expression();
        Expression* parse_cast_expression();

        Expression* parse_logical_or_expression();
        Expression* parse_logical_and_expression();

        Expression* parse_equality_expression();
        Expression* parse_relational_expression();

        Expression* parse_range_expression();

        Expression* parse_arith_expression();
        Expression* parse_term_expression();
        Expression* parse_power_expression();

        Expression* parse_bitwise_or_expression();
        Expression* parse_bitwise_xor_expression();
        Expression* parse_bitwise_and_expression();

        Expression* parse_shift_expression();

        Expression* parse_unary_expression();
        Expression* parse_postfix_expression();
        Expression* parse_primary_expression();
        Expression* parse_new_expression();
        Expression* parse_delete_expression();
        Expression* parse_parenthesis_or_tuple_or_sequence();
        Expression* parse_list_expression();
        Expression* parse_array_or_hash_expression();

        ExpressionList* parse_argument_list();

        Identifier* parse_identifier();

        TypeList* parse_generics();
        TypeList* parse_type_list(int kind);

    private:
        void advance();
        bool lookahead(int kind, int offset=0);
        bool match(int kind);
        bool match_same_line(int kind);
        bool match();
        bool expect(int kind);
        bool has_next(int offset=0);

        void indent();
        void dedent();
        bool is_indented();

        bool has_parameters();
        bool next_token_on_same_line();

    private:
        Module* module;
        Token matched;
        int idx;

        std::vector<Token> tokens;
        std::stack<int> indent_stack;
    };
}

#endif
