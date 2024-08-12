#ifndef ZLANG_TOKEN_PASS_MANAGER_H
#define ZLANG_TOKEN_PASS_MANAGER_H

#include <token_stream.h>
#include <MicroCpu.h>
#include <stack>

struct TokenList {
    std::vector<std::shared_ptr<Token>> token_list;

    inline std::shared_ptr<Token> push_token(const std::shared_ptr<Token> & token) {
        token_list.emplace_back(token);
        return token;
    }
    
    inline std::shared_ptr<Token> push_token(TokenStream & ts) {
        return push_token(ts.pull_token());
    }
    
    inline void print() {
        printf("TOKEN LIST:\n[\n");
        for (auto & token : token_list) token->print();
        printf("]\n");
    }
};

struct TokenPassManager;

struct TokenPassData {
    TokenList * token_list = nullptr;
    TokenStream * token_stream = nullptr;
    TokenPassManager * pass_manager = nullptr;
};

struct TokenPass {
    inline virtual void run(TokenPassData & data) {}
    inline virtual ~TokenPass() {}
};

struct TokenPassManager {
    private:


    public:
    MicroCpu cpu;
    
    inline TokenPassManager() {}
    virtual inline ~TokenPassManager() {}
    
    inline TokenPassManager(const TokenPassManager&m) = delete;
    inline TokenPassManager(TokenPassManager&&m) = delete;
    inline TokenPassManager & operator=(const TokenPassManager&m) const = delete;
    inline TokenPassManager & operator=(TokenPassManager&&m) const = delete;

    inline void after(std::shared_ptr<TokenPass> token_pass) {
        cpu.after([token_pass](void * user_data) mutable {
            token_pass->run(*static_cast<TokenPassData*>(user_data));
        });
    }

    inline void after(TokenPass * token_pass) {
        after(std::shared_ptr<TokenPass>(token_pass));
    }
    
    inline void insert_relative_jump_after(size_t pos, bool is_down) {
        cpu.insert_relative_jump_after(pos, is_down);
    }
    
    inline MicroCpu::ThreadContext * create_thread_context(void * user_data, std::function<void(void*)> deleter) {
        return cpu.create_thread_context(user_data, deleter);
    }

    inline MicroCpu::ThreadContext * create_thread_context(void * user_data) {
        return cpu.create_thread_context(user_data);
    }

    inline MicroCpu::ThreadContext * create_thread_context() {
        return cpu.create_thread_context();
    }

    inline MicroCpu::ThreadContext * get_current_thread_context() {
        return cpu.get_current_thread_context();
    }
    
    inline size_t get_current_instruction_pointer() {
        return cpu.get_current_instruction_pointer();
    }

    inline void destroy_thread_context(MicroCpu::ThreadContext * context) {
        cpu.destroy_thread_context(context);
    }

    inline void insert_context_switch_after(MicroCpu::ThreadContext * context) {
        cpu.insert_context_switch_after(context);
    }

    inline void insert_destroy_thread_context_after(MicroCpu::ThreadContext * context) {
        cpu.insert_destroy_thread_context_after(context);
    }

    inline void runFromStart(TokenList & list, TokenStream & stream) {
        TokenPassData data;
        data.token_list = &list;
        data.token_stream = &stream;
        data.pass_manager = this;
        cpu.exeFromStart(&data);
    }
};

struct AstContextStack {
    
    // for a contextful and contextless language
    // 
    // we must be able to parse tokens differently depending on the context
    // eg global body vs function body
    // 
    // for contextless we need only a single context that is always blank
    // for a contextful system we need a context manager to manage multiple contexts
    // 
    // each context manager is tied to the token stream and the AST
    // 
    // to enable maximum flexibility we MUST allow any kind of parsing to occur at any point
    // 
    // parsing can trigger new contexts depending on what gets parsed
    // each context is used as a hint as to what kind of parsing we should be doing
    // 
    // each context is a new stack entry on a context stack, it cannot be rewritten as it makes no sense to do so
    // 
    // 
    // 
    
    static const struct context_id_t {
        const std::unique_ptr<uint8_t> top_level { nullptr };
    } static_context_id;

    inline AstContextStack() {
        context_stack = std::stack<uint8_t*>({ static_context_id.top_level.get() });
    }

    private:
    
    std::stack<uint8_t*> context_stack;
};

#endif