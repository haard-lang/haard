#ifndef HAARD_TOKEN_H
#define HAARD_TOKEN_H

namespace haard {
    class Token {
    public:
        int get_kind() const;
        void set_kind(int newKind);

        int get_line() const;
        void setLine(int newLine);

        int get_column() const;
        void set_column(int newColumn);

        int get_whitespace() const;
        void set_whitespace(int newWhitespace);

        char* get_value() const;
        void set_value(char *newValue);

    private:
        int kind;
        int line;
        int column;
        int whitespace;
        char* value;
    };
}

#endif
