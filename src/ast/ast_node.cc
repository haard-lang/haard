#include "ast/ast_node.h"

using namespace haard;

AstNode::~AstNode() {

}

int AstNode::get_kind() const {
    return kind;
}

void AstNode::set_kind(int newKind) {
    kind = newKind;
}

const Token& AstNode::get_token() const {
    return token;
}

void AstNode::set_token(const Token& newToken) {
    token = newToken;
}
