cmake_minimum_required(VERSION 2.8)
project(hdc)

include_directories(src/include)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g -fsanitize=address")

set(STRING_POOL_SRC
    src/string_pool/string_pool.cc
)

set(TOKEN_SRC
    src/token/token.cc
)

set(AST_SRC
    src/ast/module.cc
    src/ast/import.cc
)

set(SCANNER_SRC
    src/scanner/scanner.cc
)

set(PARSER_SRC
    src/parser/parser.cc
)

set(SOURCES
    ${STRING_POOL_SRC}
    ${TOKEN_SRC}
    ${AST_SRC}
    ${SCANNER_SRC}
    ${PARSER_SRC}
    src/main.cc
)

add_executable(${PROJECT_NAME} ${SOURCES})
