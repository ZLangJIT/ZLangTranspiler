#ifndef ZLANG_TOKEN_H
#define ZLANG_TOKEN_H

#include <inttypes.h>
#include <memory>
#include <stream.h>

struct token_id_t {
    const std::unique_ptr<uint8_t> none { nullptr };
    const std::unique_ptr<uint8_t> byte { new uint8_t };
    const std::unique_ptr<uint8_t> eof { new uint8_t };
    const std::unique_ptr<uint8_t> span { new uint8_t };
};

extern const token_id_t static_token_id;

struct TokenState {
    int column;
    int line;
    Stream * stream;
    MMapIterator iter;
};

struct Token {
    void * token_id = static_token_id.none.get();
    TokenState state;
    
    inline void print_file_marker() {
        printf("%s:%d:%d", state.stream->path.c_str(), state.line, state.column);
    }
    
    virtual inline void print() {
        print_file_marker();
        printf(": Token\n");
    }
    
    inline bool is_none() {
        return token_id == static_token_id.none.get();
    }

    inline bool is_byte() {
        return token_id == static_token_id.byte.get();
    }

    inline bool is_eof() {
        return token_id == static_token_id.eof.get();
    }

    inline bool is_span() {
        return token_id == static_token_id.span.get();
    }

    template <typename T>
    T & as() {
        return *static_cast<T*>(this);
    }
};
    
struct ByteToken : Token {
    char byte;
    inline ByteToken() {
        token_id = static_token_id.byte.get();
    }

    inline void print() override {
        print_file_marker();
        printf(": ByteToken '%c'\n", byte);
    }
};

struct EOFToken : Token {
    inline EOFToken() {
        token_id = static_token_id.eof.get();
    }

    inline void print() override {
        print_file_marker();
        printf(": EOFToken\n");
    }
};

struct SpanToken : Token {
    std::shared_ptr<Token> start;
    std::shared_ptr<Token> end;
    inline SpanToken() {
        token_id = static_token_id.span.get();
    }

    inline void print() override {
        print_file_marker();
        printf(": SpanToken\n[\n");
        printf("    ");
        start->print();
        printf("    ");
        start->print();
        printf("]\n");
    }
};

#endif