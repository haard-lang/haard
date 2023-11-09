#ifndef HAARD_SCANNER_H
#define HAARD_SCANNER_H

#include <string>
#include <vector>
#include "token/token.h"

namespace haard {
    class Scanner {
    public:
        Scanner();

    public:
        std::vector<Token> read(std::string path);

    private:
        void read_to_buffer(std::string path);

        void get_token();
        void get_keyword_or_identifier();
        void skip_comment();

        bool has_next();

        bool lookahead(char c);

        bool is_alpha(int offset=0);
        bool is_digit(int offset=0);
        bool is_alphanum(int offset=0);

        void advance();
        void advance_utf8(int counter);
        void start_token();
        void create_token(int kind);

    private:
        int idx;
        int line;
        int column;
        int token_line;
        int token_column;
        int whitespace_counter;
        std::string value;
        std::string buffer;
        std::vector<Token> tokens;
    };
}
#endif
