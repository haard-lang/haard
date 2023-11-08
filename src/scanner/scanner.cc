#include <fstream>
#include "scanner/scanner.h"
#include <iostream>

void haard::Scanner::read(std::string path) {
    read_to_buffer(path);
    std::cout << buffer << std::endl;
}

void haard::Scanner::read_to_buffer(std::string path) {
    char c;
    std::ifstream file;

    file.open(path.c_str());

    while (file.get(c)) {
        buffer += c;
    }

    file.close();
}
