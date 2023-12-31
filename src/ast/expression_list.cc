#include <sstream>
#include "ast/expression_list.h"

using namespace haard;

ExpressionList::~ExpressionList() {
    for (int i = 0; i < expressions.size(); ++i) {
        delete expressions[i];
    }
}

Expression* ExpressionList::get_expression(int idx) {
    if (idx < expressions.size()) {
        return expressions[idx];
    }

    return nullptr;
}

void ExpressionList::add_expression(Expression* expression) {
    expressions.push_back(expression);
}

int ExpressionList::expressions_count() {
    return expressions.size();
}
