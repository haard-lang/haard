#ifndef HAARD_AST_NODE_H
#define HAARD_AST_NODE_H

namespace haard {
    typedef enum AstKind {
        AST_MODULE,
        AST_FUNCTION,
        AST_IMPORT
    } AstKind;

    class AstNode {
    public:
        int get_kind() const;
        void set_kind(int newKind);

    private:
        int kind;
    };
}

#endif
