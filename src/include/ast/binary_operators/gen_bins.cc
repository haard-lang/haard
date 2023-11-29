#include <iostream>
#include <fstream>
#include <sstream>

char to_upper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }

    return c;
}

std::string to_upper(std::string s) {
    std::stringstream ss;

    for (int i = 0; i < s.size(); ++i) {
        ss << to_upper(s[i]);
    }

    return ss.str();
}

std::string to_camel(std::string s) {
    std::stringstream ss;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '_') {
            ++i;
            ss << to_upper(s[i]);
        } else if (i == 0) {
            ss << to_upper(s[i]);
        } else {
            ss << s[i];
        }
    }

    return ss.str();
}

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

void gen_file(std::string path) {
    std::ofstream file(path + ".h");

    std::string kind = "AST_" + to_upper(path);
    std::string class_name = to_camel(path);
    file << gen(kind, class_name);
    file.close();
}

int main() {
    gen_file("assignment");
    gen_file("bitwise_and_assignment");
    gen_file("bitwise_xor_assignment");
    gen_file("bitwise_or_assignment");
    gen_file("bitwise_not_assignment");
    gen_file("division_assignment");
    gen_file("integer_division_assignment");
    gen_file("minus_assignment");
    gen_file("modulo_assignment");
    gen_file("plus_assignment");
    gen_file("times_assignment");
    gen_file("shift_left_logical_assignment");
    gen_file("shift_right_arithmetic_assignment");
    gen_file("shift_right_logical_assignment");

    gen_file("logical_or");
    gen_file("logical_and");

    gen_file("equal");
    gen_file("not_equal");

    gen_file("less_than");
    gen_file("greater_than");
    gen_file("less_than_or_equal");
    gen_file("greater_than_or_equal");

    gen_file("in");
    gen_file("not_in");

    gen_file("inclusive_range");
    gen_file("exclusive_range");

    gen_file("plus");
    gen_file("minus");

    gen_file("times");
    gen_file("division");
    gen_file("modulo");
    gen_file("integer_division");

    gen_file("power");
    
    gen_file("bitwise_or");
    gen_file("bitwise_xor");
    gen_file("bitwise_and");

    gen_file("shift_left_logical");
    gen_file("shift_right_arithmetic");
    gen_file("shift_right_logical");

    gen_file("dot");
    gen_file("arrow");
    gen_file("index");

    return 0;
}
