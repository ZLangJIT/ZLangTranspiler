#ifndef ZLANG_TOKEN_COMBINATOR_H
#define ZLANG_TOKEN_COMBINATOR_H

#include <token_pass_manager.h>
#include <type_traits>

struct MatchData : TokenPassData {
    std::shared_ptr<Token> start;
    std::shared_ptr<Token> end;
    
    // keep a local TokenList and merge with previous results on success else throw away
    //
    TokenList list;
    
    bool matched;
    
    inline void reset_match_data() {
        start.reset();
        end.reset();
        list = std::move(TokenList());
        matched = false;
    }
    
    inline MatchData() { reset_match_data(); }
    inline virtual ~MatchData() {}
};

struct Pass : TokenPass {

    // rewriting can be done by using a "read index" and a "write index"
    // in order to keep track of where we are "reading from" and where we are "writing to"
    //
    
    // BACKTRACKING ...
    //
    // this can be implemented via a save/restore stack
    //
    // we save the stack, push a rule to be executed after the current rule, then pop of the rule fails to match
    //
    //
    
    TokenPassData * data;

    typedef std::function<void(MatchData&local)> Action;
    Action default_action;
    
    inline Pass(Action a = [](MatchData&){}) : default_action(a) {}
    
    inline virtual void match(MatchData & m) {}
    
    inline void reset_match_data(MatchData & x) {
        data = static_cast<TokenPassData*>(&x);
        x.reset_match_data();
    }

    inline virtual void run(MatchData & x) {
        reset_match_data(x);
        match(x);
    }

    inline void run(TokenPassData & x) override final {
        run(*static_cast<MatchData*>(static_cast<void*>(&x)));
    }
    
    inline TokenState save() {
        return data->token_stream->save();
    }
    
    inline void load(TokenState & s) {
        data->token_stream->load(s);
    }

    inline std::shared_ptr<Token> next() {
        return data->token_stream->pull_token();
    }
};

struct SinglePass : Pass {
    inline SinglePass(Action a = [](MatchData&){}) : Pass(a) {}
    inline void run(MatchData & x) override final { Pass::run(x); }
};

struct CustomPass : Pass {
    inline CustomPass(Action a = [](MatchData&){}) : Pass(a) {}
    inline virtual void run(MatchData & x) override { Pass::run(x); }
};

struct TokenPassLambdaAdapter : TokenPass {
    std::function<void(TokenPassData&)> f;
    inline TokenPassLambdaAdapter() : f([](TokenPassData&u){}) {}
    inline TokenPassLambdaAdapter(std::function<void(TokenPassData&)> f) : f(f) {}
    inline void run(TokenPassData & user_data) override { f(user_data); };
};

struct PassLambdaAdapter : Pass {
    std::function<void(MatchData&)> f;
    inline PassLambdaAdapter() : f([](MatchData&u){}) {}
    inline PassLambdaAdapter(std::function<void(MatchData&)> f) : f(f) {}
    inline void run(MatchData & user_data) override { f(user_data); };
};

// for debugging / informational
//
struct Echo : SinglePass {
    const char * msg;
    inline Echo(const char * msg) : msg(msg) {}
    inline void match(MatchData & m) override {
        printf("%s\n", msg);
        m.matched = true;
    }
};

struct Char : SinglePass {
    char ch;
    inline Char(const char & c, Action a = [](MatchData&){}) : ch(c), SinglePass(a) {}
    inline void match(MatchData & m) override {
        MatchData local;
        auto s = save();
        local.start = next();
        local.end = local.start;
        if (!local.start->is_eof()) {
            char ch2 = local.end->as<ByteToken>().byte;
            if (ch2 == ch) {
                local.matched = true;
                local.list.push_token(local.end);
                default_action(local);
                return;
            }
        }
        load(s);
    }
};

struct String : SinglePass {
    std::string str;
    inline String(const std::string & str, Action a = [](MatchData&){}) : str(str), SinglePass(a) {}
    inline void match(MatchData & m) override {
        auto s = save();
        MatchData local;
        local.start = next();
        local.end = local.start;
        size_t e = str.size();
        if (e != 0) {
            size_t e_minus_one = e-1;
            size_t i = 0;
            while (!local.end->is_eof()) {
                char ch = str[i];
                char ch2 = local.end->as<ByteToken>().byte;
                if (ch != ch2) {
                    break;
                }
                if (i == e_minus_one) {
                    local.matched = true;
                    local.list.push_token(local.end);
                    default_action(local);
                    return;
                }
                local.list.push_token(local.end);
                local.end = next();
                i++;
            }
        }
        load(s);
        return;
    }
};

struct Range : SinglePass {
    std::vector<char> range;
    
    template <typename ... T, typename = std::enable_if_t<(std::is_same_v<T, char> && ...)>>
    inline Range(T ... low_high, Action a = [](MatchData&){}) : range({low_high ...}), SinglePass(a) {}

    inline void match(MatchData & m) override {
        auto s = save();
        MatchData local;
        local.start = next();
        local.end = local.start;
        size_t e = range.size();
        if (e != 0) {
            size_t e_minus_one = e-1;
            size_t i = 0;
            bool end_of_ranges = false;
            while (!local.end->is_eof()) {
                char ch = local.end->as<ByteToken>().byte;
                // see if we are in range
                while (true) {
                    char low = range[i];
                    if (ch < low) {
                        printf("character '%c' is not in range of low '%c'\n", ch, low);
                        // we are not in range, see if we have another range
                        i++;
                        i++;
                        if (i >= e) {
                            printf("no more ranges, i = %zu, e = %zu\n", i, e);
                            // we have no more ranges
                            end_of_ranges = true;
                            break;
                        }
                        // we have more ranges, try them
                        continue;
                    }
                    // we are in range, see if we have an upper range
                    printf("character '%c' is in range of low '%c'\n", ch, low);
                    i++;
                    if (i >= e) {
                        // we have no upper range
                        local.matched = true;
                    } else {
                        // we have an upper range, see if we are in range
                        char high = range[i];
                        if (ch > high) {
                            // we are not in high range, but we are in low range
                            // eg,  ch == 6, low == 2 hi == 4
                            printf("character '%c' is not in range of high '%c'\n", ch, high);
                            // see if we have more ranges
                            i++;
                            i++;
                            if (i >= e) {
                                printf("no more ranges, i = %zu, e = %zu\n", i, e);
                                // we have no more ranges
                                end_of_ranges = true;
                                break;
                            }
                            // we have more ranges, try them
                            continue;
                        }
                        printf("character '%c' is in range of high '%c'\n", ch, high);
                    }
                    // we are in range, look at next character
                    i = 0;
                    local.matched = true;
                    local.list.push_token(local.end);
                    local.end = next();
                    break;
                }
                if (end_of_ranges) {
                    break;
                }
            }
            // we reached EOF
        }
        if (local.matched) {
            local.list.push_token(local.end);
            default_action(local);
            printf("matched range\n");
        } else {
            // we failed to find any ranges at all
            printf("failed to match range\n");
            load(s);
        }
        return;
    }
};

struct Or : CustomPass {
    
    private:
    std::vector<std::shared_ptr<Pass>> passes;
    
    public:
    
    inline Or(const std::initializer_list<Pass*> & passes, Action a = [](MatchData&){}) : CustomPass(a) {
        for(Pass* p : passes)
            this->passes.emplace_back(p);
    }

    inline void run(MatchData & x) override {
        // TODO: should we REALLY do this?
        // x is effectively a global and we reset it at every OR invocation
        //
        // since OR can include itself OR { OR { a, b }, OR { c, d } }
        //
        reset_match_data(x);
        

        // takes advantage of dynamic insertion to generate new instructions
        //
        x.pass_manager->after(new PassLambdaAdapter([this](MatchData&x) {
            size_t e = passes.size();
            if (e != 0) {
                printf("OR PASS running passes ...\n");
                
                // init variables here
                //
                size_t i = 0;
                MatchData local;

                std::shared_ptr<PassLambdaAdapter> self = std::shared_ptr<PassLambdaAdapter>(new PassLambdaAdapter());
                self->f = [self, this, local, i, &e](MatchData&x) mutable {
                    //
                    // variables get copied above from initialization
                    
                    if (i != e) {
                        x.pass_manager->after(new PassLambdaAdapter([self, this, &local, &i, &e](MatchData&x) mutable {
                            printf("OR PASS   running pass %zu ...\n", i);
                            passes[i]->run(x);
                            x.pass_manager->after(new PassLambdaAdapter([self, this, &local, &i, &e](MatchData&x) mutable {
                                printf("OR PASS   ran pass %zu\n", i);
                                if (x.matched) {
                                    printf("OR PASS early match\n");
                                    local.matched = true;
                                    default_action(local);
                                } else if (i == e-1) {
                                    printf("OR PASS match failed\n");
                                } else {
                                    i++;
                                    x.pass_manager->after(self);
                                }
                            }));
                        }));
                    }
                };
                x.pass_manager->after(self);
            }
        }));
    }
};

std::shared_ptr<std::pair<MicroCpu::ThreadContext*, MicroCpu::ThreadContext*>> pushParseContext(TokenPassManager & pm) {
    std::shared_ptr<std::pair<MicroCpu::ThreadContext*, MicroCpu::ThreadContext*>> context { new std::pair<MicroCpu::ThreadContext*, MicroCpu::ThreadContext*>({nullptr, nullptr}) };
    
    pm.after(new TokenPassLambdaAdapter([&pm, context] (TokenPassData&x) mutable {
        context->first = pm.get_current_thread_context();
        MatchData * m = new MatchData();
        static_cast<TokenPassData&>(*m) = x;
        context->second = pm.create_thread_context(m, [](void*p){ puts("deleting context"); delete static_cast<MatchData*>(p);});
        pm.insert_context_switch_after(context->second);
    }));
    
    return context;
}

void popParseContext(TokenPassManager & pm, std::shared_ptr<std::pair<MicroCpu::ThreadContext*, MicroCpu::ThreadContext*>> & context) {
    pm.after(new PassLambdaAdapter([&pm, context] (MatchData&x) mutable {
        pm.insert_context_switch_after(context->first);
        pm.insert_destroy_thread_context_after(context->second);
    }));
}

#endif