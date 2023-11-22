#include "ast/minus.h"

using namespace haard;

Minus::Minus(Expression* left, Expression* right) {
    set_kind(AST_MINUS);
    set_left(left);
    set_right(right);
}

Minus::Minus(Token& token, Expression* left, Expression* right) {
    set_kind(AST_MINUS);
    set_left(left);
    set_right(right);
    set_token(token);
}
