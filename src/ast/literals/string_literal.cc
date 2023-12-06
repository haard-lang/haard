#include "ast/literals/string_literal.h"

using namespace haard;

StringLiteral::StringLiteral(Token& token) {
    set_kind(EXPR_LITERAL_STRING);
    set_token(token);
}
