#include <iostream>
#include <fstream>
#include <sstream>

std::string gen(std::string kind, std::string class_name, std::string header) {
    std::stringstream ss;

    ss << "#include \"ast/" << header << ".h\"\n\n";

    ss << "using namespace haard;\n\n";

    ss << class_name << "::" << class_name;
    ss << "(Expression* left, Expression* right) {\n";
    ss << "    set_kind(" << kind << ");\n";
    ss << "    set_left(left);\n";
    ss << "    set_right(right);\n";
    ss << "}\n\n";

    ss << class_name << "::" << class_name;
    ss << "(Token& token, Expression* left, Expression* right) {\n";
    ss << "    set_kind(" << kind << ");\n";
    ss << "    set_left(left);\n";
    ss << "    set_right(right);\n";
    ss << "    set_token(token);\n";
    ss << "}\n";

    return ss.str();
}

void gen_file(std::string path, std::string kind, std::string class_name, std::string header) {
    std::ofstream file(path);

    file << gen(kind, class_name, header);
    file.close();
}


int main() {
    gen_file("plus.cc", "AST_PLUS", "Plus", "plus");
    gen_file("minus.cc", "AST_MINUS", "Minus", "minus");

    gen_file("times.cc", "AST_TIMES", "Times", "times");
    gen_file("division.cc", "AST_DIVISION", "Division", "division");
    gen_file("modulo.cc", "AST_MODULO", "Modulo", "modulo");
    gen_file("integer_division.cc", "AST_INTEGER_DIVISION", "IntegerDivision", "integer_division");
    return 0;
}
