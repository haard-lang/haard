#ifndef HAARD_DECLARATION_H
#define HAARD_DECLARATION_H

#include "ast/ast_node.h"
#include "token/token.h"

namespace haard {
    class Declaration : public AstNode {
    public:
        const Token& get_name() const;
        void set_name(const Token& newName);

    private:
        Token name;
    };
}
#endif
