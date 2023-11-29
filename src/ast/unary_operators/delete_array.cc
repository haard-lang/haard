#include "ast/unary_operators/delete_array.h"

using namespace haard;

DeleteArray::DeleteArray(Expression* expression) {
    set_kind(EXPR_DELETE_ARRAY);
    set_expression(expression);
}

DeleteArray::DeleteArray(Token& token, Expression* expression) {
    set_kind(EXPR_DELETE_ARRAY);
    set_expression(expression);
    set_token(token);
}
