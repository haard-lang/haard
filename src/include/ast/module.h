#ifndef HAARD_MODULE_H
#define HAARD_MODULE_H

#include <vector>
#include "ast/ast_node.h"
#include "ast/declaration.h"
#include "ast/import.h"
#include "ast/function.h"

namespace haard {
    class Module : public AstNode {
    public:
        Module();
        ~Module();

    public:
        void add_import(Import* import);
        int imports_count();
        Import* get_import(int idx);

        void add_function(Function* function);
        int functions_count();
        Function* get_function(int idx);

        int declarations_count();
        Declaration* get_declaration(int idx);

    private:
        std::vector<Import*> imports;
        std::vector<Function*> functions;
        std::vector<Declaration*> declarations;
    };
}

#endif
