#include "ast/binary_operators/bitwise_xor.h"

using namespace haard;

BitwiseXor::BitwiseXor(Expression* left, Expression* right) {
    set_kind(EXPR_BITWISE_XOR);
    set_left(left);
    set_right(right);
}

BitwiseXor::BitwiseXor(Token& token, Expression* left, Expression* right) {
    set_kind(EXPR_BITWISE_XOR);
    set_left(left);
    set_right(right);
    set_token(token);
}
