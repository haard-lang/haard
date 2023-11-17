#include "ast/compound_statement.h"

using namespace haard;

CompoundStatement::CompoundStatement() {
    set_kind(AST_COMPOUND_STATEMENT);
}

CompoundStatement::~CompoundStatement() {
    for (auto s : statements) {
        delete s;
    }
}

void CompoundStatement::add_statement(Statement* stmt) {
    statements.push_back(stmt);
}

int CompoundStatement::statements_count() {
    return statements.size();
}

Statement* CompoundStatement::get_statement(int idx) {
    return statements[idx];
}
