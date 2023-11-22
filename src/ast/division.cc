#include "ast/division.h"

using namespace haard;

Division::Division(Expression* left, Expression* right) {
    set_kind(AST_DIVISION);
    set_left(left);
    set_right(right);
}

Division::Division(Token& token, Expression* left, Expression* right) {
    set_kind(AST_DIVISION);
    set_left(left);
    set_right(right);
    set_token(token);
}
