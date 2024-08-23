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
    
struct TokenList {
    std::vector<std::shared_ptr<Token>> token_list;

    inline std::shared_ptr<Token> push_token(const std::shared_ptr<Token> & token) {
        token_list.emplace_back(token);
        return token;
    }
    
    inline void print() {
        printf("TOKEN LIST:\n[\n");
        for (auto & token : token_list) token->print();
        printf("]\n");
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

    inline void load(const TokenState & data) {
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

struct SpanToken : Token {
    std::shared_ptr<Token> start;
    std::shared_ptr<Token> end;
    inline SpanToken() {
        token_id = static_token_id.span.get();
    }
    
    inline virtual std::string extract_string() {
        std::string str;
        TokenStream s;
        s.load(start->state);
        auto & es = end->state;
        while (true) {
            auto tok_ptr = s.pull_token();
            auto & tok = tok_ptr->as<ByteToken>();
            if (!tok.is_eof()) {
                str.push_back(tok.byte);
            }
            if (tok.state.line == es.line && tok.state.column == es.column) break;
        }
        return str;
    }

    inline void collapse(TokenList & token_list) {
        start = token_list.token_list[0];
        state = start->state;
        end = token_list.token_list[token_list.token_list.size()-1];
        token_list = std::move(TokenList());
        token_list.token_list.emplace_back(this);
    }

    inline void print() override {
        print_file_marker();
        auto content = extract_string();
        printf(": SpanToken: \"%s\"\n", content.c_str());
    }
};

#endif