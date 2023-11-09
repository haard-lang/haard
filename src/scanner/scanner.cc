#include <fstream>
#include "scanner/scanner.h"
#include "token/token.h"
#include "string_pool/string_pool.h"
#include <iostream>

using namespace haard;

Scanner::Scanner() {
    line = 1;
    column = 1;
    idx = 0;
}

std::vector<Token> Scanner::read(std::string path) {
    read_to_buffer(path);

    while (has_next()) {
        get_token();
    }

    return tokens;
}

void Scanner::read_to_buffer(std::string path) {
    char c;
    std::ifstream file;

    file.open(path.c_str());

    while (file.get(c)) {
        buffer += c;
    }

    file.close();
}

void Scanner::get_token() {
    if (is_alpha()) {
        get_keyword_or_identifier();
    } else if (lookahead(' ')) {
        advance();
    } else if (lookahead('\n')) {
        advance();
    }
}

void Scanner::get_keyword_or_identifier() {
    start_token();

    while (is_alphanum()) {
        advance();
    }

    create_token(0);
}

bool Scanner::has_next() {
    return idx < buffer.size();
}

bool Scanner::lookahead(char c) {
    return has_next() && buffer[idx] == c;
}

bool Scanner::is_alpha(int offset) {
    char c = buffer[idx + offset];

    return c >= 'a' && c <= 'z' ||
           c >= 'A' && c <= 'Z' ||
           c == '_' ||
            ((c >> 7) & 0x1) == 1;
}

bool Scanner::is_digit(int offset) {
    return buffer[idx + offset] >= '0' && buffer[idx + offset] <= '9';
}

bool Scanner::is_alphanum(int offset) {
    return is_alpha(offset) || is_digit(offset);
}

void Scanner::advance() {
    if (!has_next()) {
        return;
    }

    if (buffer[idx] == '\n') {
        line++;
        column = 1;
        whitespace_counter = 0;
    } else {
        column++;
    }

    value += buffer[idx];
    idx++;
}

void Scanner::start_token() {
    value = "";
    token_line = line;
    token_column = column;
}

void Scanner::create_token(int kind) {
    Token token;

    token.set_kind(kind);
    token.set_value(StringPool::get(value));
    token.set_line(token_line);
    token.set_column(token_column);
    token.set_whitespace(whitespace_counter);
    /*token.set_begin(token_begin);
    token.set_end(idx);*/

    tokens.push_back(token);
}
