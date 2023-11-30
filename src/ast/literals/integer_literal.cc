#include "ast/literals/integer_literal.h"

using namespace haard;

IntegerLiteral::IntegerLiteral(Token& token) {
    set_kind(EXPR_LITERAL_INTEGER);
    set_token(token);
}
