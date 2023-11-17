#ifndef HAARD_COMPOUND_STATEMENT_H
#define HAARD_COMPOUND_STATEMENT_H

#include <vector>
#include "ast/statement.h"

namespace haard {
    class CompoundStatement : public Statement {
    public:
        CompoundStatement();
        ~CompoundStatement();

    public:
        void add_statement(Statement* stmt);
        int statements_count();
        Statement* get_statement(int idx);

    private:
        std::vector<Statement*> statements;
    };
}

#endif
