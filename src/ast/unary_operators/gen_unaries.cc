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

std::string gen(std::string kind, std::string class_name, std::string header) {
    std::stringstream ss;

    ss << "#include \"ast/unary_operators/" << header << ".h\"\n\n";

    ss << "using namespace haard;\n\n";

    ss << class_name << "::" << class_name;
    ss << "(Expression* expression) {\n";
    ss << "    set_kind(" << kind << ");\n";
    ss << "    set_expression(expression);\n";
    ss << "}\n\n";

    ss << class_name << "::" << class_name;
    ss << "(Token& token, Expression* expression) {\n";
    ss << "    set_kind(" << kind << ");\n";
    ss << "    set_expression(expression);\n";
    ss << "    set_token(token);\n";
    ss << "}\n";

    return ss.str();
}

void gen_file(std::string header) {
    std::string kind = "EXPR_" + to_upper(header);
    std::string class_name = to_camel(header);
    std::ofstream file(header + ".cc");

    file << gen(kind, class_name, header);
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
    gen_file("delete");
    gen_file("delete_array");

    return 0;
}
