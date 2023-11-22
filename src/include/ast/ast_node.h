#ifndef HAARD_AST_NODE_H
#define HAARD_AST_NODE_H

#include "token/token.h"

namespace haard {
    typedef enum AstKind {
        AST_MODULE,
        AST_FUNCTION,
        AST_IMPORT,
        AST_ID,

        AST_UNKNOWN_STATEMENT,
        AST_COMPOUND_STATEMENT,
        AST_EXPRESSION_STATEMENT,

        AST_EXPRESSION_UNKNOWN,
        AST_ASSIGNMENT,

        AST_PLUS,
        AST_MINUS,

        AST_TIMES,
        AST_DIVISION,

        AST_UNARY_PLUS,

        AST_BOOL,
        AST_CHAR,
        AST_UCHAR,
        AST_SHORT,
        AST_USHORT,
        AST_INT,
        AST_UINT,
        AST_LONG,
        AST_ULONG,
        AST_FLOAT,
        AST_DOUBLE,
        AST_I8,
        AST_U8,
        AST_I16,
        AST_U16,
        AST_I32,
        AST_U32,
        AST_I64,
        AST_U64,
        AST_F32,
        AST_F64,
        AST_SYMBOL,
        AST_VOID,
        AST_POINTER,
        AST_REFERENCE,
        AST_LIST,
        AST_ARRAY,
        AST_STR,
        AST_NAMED,
        AST_TUPLE_TYPE,
        AST_FUNCTION_TYPE,
        AST_GENERICS
    } AstKind;

    class AstNode {
    public:
        virtual ~AstNode();

    public:
        int get_kind() const;
        void set_kind(int newKind);

        const Token &get_token() const;
        void set_token(const Token &newToken);

    private:
        int kind;
        Token token;
    };
}

#endif
