#include "ast/literals/double_literal.h"

using namespace haard;

DoubleLiteral::DoubleLiteral(Token& token) {
    set_kind(EXPR_LITERAL_DOUBLE);
    set_token(token);
}
