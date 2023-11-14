#ifndef HAARD_IDENTIFIER_H
#define HAARD_IDENTIFIER_H

#include "token/token.h"
#include "ast/ast_node.h"
#include "ast/generics.h"

namespace haard {
    class Identifier : public AstNode {
    public:
        Identifier();
        Identifier(Token& alias, Token& name, bool alias_flag, bool global_flag, Generics* generics);
        ~Identifier();

        const Token& get_name() const;
        void set_name(const Token& newName);

        const Token& get_alias() const;
        void set_alias(const Token& newAlias);

        bool has_global_alias();
        bool has_alias();

        Generics* get_generics() const;
        void set_generics(Generics *newGenerics);

    private:
        Token name;
        Token alias;
        bool alias_flag;
        bool global_alias_flag;
        Generics* generics;
    };
}

#endif
