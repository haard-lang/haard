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
    char c = buffer[idx];

    if (!has_next()) {
        return;
    }

    if (c == '\n') {
        line++;
        column = 1;
        whitespace_counter = 0;
        value += c;
        idx++;
    } else {
        if (((c >> 7) & 0x1) == 0) {
            column++;
            value += c;
            idx++;
        } else if (((c >> 5) & 0x7) == 6) {
            int counter = 2;

            while (has_next() && counter > 0) {
                value += buffer[idx];
                idx++;
                --counter;
            }

            column++;
        } else if (((c >> 4) & 0xf) == 0xe) {
            int counter = 3;

            while (has_next() && counter > 0) {
                value += buffer[idx];
                idx++;
                --counter;
            }

            column++;
        } else if (((c >> 3) & 0x1f) == 0x1e) {
            int counter = 4;

            while (has_next() && counter > 0) {
                value += buffer[idx];
                idx++;
                --counter;
            }

            column++;
        }
    }
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
