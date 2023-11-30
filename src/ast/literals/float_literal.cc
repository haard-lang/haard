#include "ast/literals/float_literal.h"

using namespace haard;

FloatLiteral::FloatLiteral(Token& token) {
    set_kind(EXPR_LITERAL_FLOAT);
    set_token(token);
}
