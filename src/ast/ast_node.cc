#include "ast/ast_node.h"

using namespace haard;

int AstNode::get_kind() const {
    return kind;
}

void AstNode::set_kind(int newKind) {
    kind = newKind;
}
