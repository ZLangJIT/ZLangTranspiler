#ifndef ZLANG_TOKEN_STREAM_H
#define ZLANG_TOKEN_STREAM_H

#include <token.h>
#include <mutex>

struct TokenStream {
    private:
    int column = 1;
    int line = 1;

    public:
    
    inline int get_column() { return column; }
    inline int get_line() { return line; }

    Stream * stream = nullptr;
    
    inline TokenState save() {
        return {column, line, stream, stream == nullptr ? MMapIterator() : stream->iter() };
    }

    inline void load(TokenState & data) {
        column = data.column;
        line = data.line;
        stream = data.stream;
        if (stream != nullptr) {
            stream->iter() = data.iter;
        }
    }

    private:
    
    template<typename iter_in, typename iter_end>
    std::shared_ptr<Token> pull_token(iter_in & input, iter_end & end) {
        if (input == end) {
            std::shared_ptr<Token> t {new EOFToken()};
            t->state = save();
            return t;
        } else {
            std::shared_ptr<Token> t {new ByteToken()};
            t->state = save();
            t->as<ByteToken>().byte = *input;
            input++;
            column++;
            if (t->as<ByteToken>().byte == '\n') {
                column = 1;
                line++;
            }
            return t;
        }
    }
    
    public:
    
    inline std::shared_ptr<Token> pull_token() {
        Stream & it = *stream;
        return pull_token(it.iter(), it.end());
    }
};

#endif