#include <iostream>
#include <fstream>
#include <sstream>

std::string gen(std::string kind, std::string class_name) {
    std::stringstream ss;

    ss << "#ifndef HAARD_" << kind << "_H\n";
    ss << "#define HAARD_" << kind << "_H\n\n";

    ss << "#include \"binary_operator.h\"\n\n";

    ss << "namespace haard {\n";
    ss << "    class " << class_name << " : public BinaryOperator {\n";
    ss << "    public:\n";
    ss << "        " << class_name << "(Expression* left=nullptr, Expression* right=nullptr);\n";
    ss << "        " << class_name << "(Token& token, Expression* left=nullptr, Expression* right=nullptr);\n";
    ss << "    };\n";
    ss << "}\n\n";

    ss << "#endif";

    return ss.str();
}

void gen_file(std::string path, std::string kind, std::string class_name) {
    std::ofstream file(path);

    file << gen(kind, class_name);
    file.close();
}

int main() {
    gen_file("plus.h", "AST_PLUS", "Plus");
    gen_file("minus.h", "AST_MINUS", "Minus");

    gen_file("times.h", "AST_TIMES", "Times");
    gen_file("division.h", "AST_DIVISION", "Division");
    gen_file("modulo.h", "AST_MODULO", "Modulo");
    gen_file("integer_division.h", "AST_INTEGER_DIVISION", "IntegerDivision");

    return 0;
}
