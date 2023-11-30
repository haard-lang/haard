#include "ast/literals/char_literal.h"

using namespace haard;

CharLiteral::CharLiteral(Token& token) {
    set_kind(EXPR_LITERAL_CHAR);
    set_token(token);
}
