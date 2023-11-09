#include <fstream>
#include "scanner/scanner.h"
#include "token/token.h"
#include "string_pool/string_pool.h"
#include <iostream>
#include <map>

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
    if (lookahead('#')) {
        skip_comment();
    } else if (lookahead('\n')) {
        advance();
        count_leading_whitespace();
    } else if (lookahead(' ')) {
        advance();
    } else if (is_alpha()) {
        get_keyword_or_identifier();
    } else if (is_digit()) {
        get_number();
    }
}

void Scanner::get_keyword_or_identifier() {
    int kind;

    start_token();

    while (is_alphanum()) {
        advance();
    }

    kind = TK_ID;

    if (value_to_token_kind_map.count(value) > 0) {
        kind = value_to_token_kind_map.at(value);
    }

    create_token(kind);
}

void Scanner::get_number() {
    int kind = TK_LITERAL_INTEGER;

    start_token();

    if (has_base()) {
        advance();

        if (lookahead('b')) {
            advance();

            while (is_binary_digit() || lookahead('_')) {
                advance();
            }
        } else if (lookahead('o')) {
            advance();

            while (is_octal_digit() || lookahead('_')) {
                advance();
            }
        } else if (lookahead('x')) {
            advance();

            while (is_hex_digit() || lookahead('_')) {
                advance();
            }
        } else {
            while (is_octal_digit() || lookahead('_')) {
                advance();
            }
        }
    } else {
        while (is_digit() || lookahead('_')) {
            advance();
        }

        if (lookahead('.') && !lookahead('.', 1)) {
            advance();
            kind = TK_LITERAL_DOUBLE;

            while (is_digit()) {
                advance();
            }
        }

        if (lookahead('e') || lookahead('E')) {
            kind = TK_LITERAL_DOUBLE;
            advance();

            if (lookahead('-') || lookahead('+')) {
                advance();
            }

            while (is_digit()) {
                advance();
            }
        }

        if (lookahead('f') || lookahead('F')) {
            advance();
            kind = TK_LITERAL_FLOAT;
        }
    }

    create_token(kind);
}

void Scanner::skip_comment() {
    while (!lookahead('\n')) {
        advance();
    }
}

bool Scanner::has_next(int count) {
    return idx + count < buffer.size();
}

bool Scanner::lookahead(char c, int offset) {
    return has_next(offset) && buffer[idx + offset] == c;
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

bool Scanner::has_base() {
    bool flag;
    bool flag2;

    if (!has_next(2)) return false;

    char c1 = buffer[idx + 1];
    char c0 = buffer[idx];

    flag = c1 == 'o' || c1 == 'b' || c1 == 'x';
    flag2 = c1 >= '0' && c1 <= '7';

    return c0 == '0' && (flag || flag2);
}

bool Scanner::is_binary_digit() {
    return buffer[idx] == '0' || buffer[idx] == '1';
}

bool Scanner::is_octal_digit() {
    return buffer[idx] >= '0' && buffer[idx] <= '7';
}

bool Scanner::is_hex_digit() {
    return buffer[idx] >= '0' && buffer[idx] <= '9' ||
           buffer[idx] >= 'a' && buffer[idx] <= 'f' ||
           buffer[idx] >= 'A' && buffer[idx] <= 'F';
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
            advance_utf8(1);
        } else if (((c >> 5) & 0x7) == 6) {
            advance_utf8(2);
        } else if (((c >> 4) & 0xf) == 0xe) {
            advance_utf8(3);
        } else if (((c >> 3) & 0x1f) == 0x1e) {
            advance_utf8(4);
        }
    }
}

void Scanner::advance_utf8(int counter) {
    while (has_next() && counter > 0) {
        value += buffer[idx];
        idx++;
        --counter;
    }

    column++;
}

void Scanner::count_leading_whitespace() {
    whitespace_counter = 0;

    while (lookahead(' ')) {
        advance();
        whitespace_counter++;
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
