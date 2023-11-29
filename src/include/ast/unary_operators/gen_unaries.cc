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

    ss << "#include \"unary_operator.h\"\n\n";

    ss << "namespace haard {\n";
    ss << "    class " << class_name << " : public UnaryOperator {\n";
    ss << "    public:\n";
    ss << "        " << class_name << "(Expression* expression=nullptr);\n";
    ss << "        " << class_name << "(Token& token, Expression* expression=nullptr);\n";
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
    gen_file("unary_minus");
    gen_file("unary_plus");
    gen_file("address_of");
    gen_file("dereference");
    gen_file("logical_not");
    gen_file("bitwise_not");
    gen_file("pre_increment");
    gen_file("pre_decrement");
    gen_file("pos_increment");
    gen_file("pos_decrement");
    gen_file("sizeof");
    gen_file("new");
    gen_file("delete");
    gen_file("delete_array");

    return 0;
}
