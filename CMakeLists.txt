cmake_minimum_required(VERSION 2.8)
project(hdc)

include_directories(src/include)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g -fsanitize=address")

set(STRING_POOL_SRC
    src/string_pool/string_pool.cc
)

set(TYPE_POOL_SRC
    src/type_pool/type_pool.cc
)

set(TOKEN_SRC
    src/token/token.cc
)

set(AST_SRC
    src/ast/ast_node.cc
    src/ast/declaration.cc
    src/ast/module.cc
    src/ast/import.cc
    src/ast/function.cc
    src/ast/variable.cc
    src/ast/type.cc
    src/ast/subtyped_type.cc
    src/ast/named_type.cc
    src/ast/type_list.cc
    src/ast/statement.cc
    src/ast/compound_statement.cc
    src/ast/expression_statement.cc
    src/ast/expression.cc
    src/ast/binary_operator.cc
    src/ast/identifier.cc
)

set(SCANNER_SRC
    src/scanner/scanner.cc
)

set(PARSER_SRC
    src/parser/parser.cc
)

set(PRETTY_PRINTER_SRC
    src/pretty_printer/pretty_printer.cc
)

set(SOURCES
    ${STRING_POOL_SRC}
    ${TYPE_POOL_SRC}
    ${TOKEN_SRC}
    ${AST_SRC}
    ${SCANNER_SRC}
    ${PARSER_SRC}
    ${PRETTY_PRINTER_SRC}
    src/main.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})
