#include "token/token.h"

using namespace haard;

int Token::get_kind() const {
    return kind;
}

void Token::set_kind(int newKind) {
    kind = newKind;
}

int Token::get_line() const {
    return line;
}

void Token::setLine(int newLine) {
    line = newLine;
}

int Token::get_column() const {
    return column;
}

void Token::set_column(int newColumn) {
    column = newColumn;
}

int Token::get_whitespace() const {
    return whitespace;
}

void Token::set_whitespace(int newWhitespace) {
    whitespace = newWhitespace;
}

char *Token::get_value() const {
    return value;
}

void Token::set_value(char *newValue) {
    value = newValue;
}
