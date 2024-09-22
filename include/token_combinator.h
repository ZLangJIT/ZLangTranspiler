#ifndef ZLANG_TOKEN_COMBINATOR_H
#define ZLANG_TOKEN_COMBINATOR_H

#include <token.h>
#include <MicroCpu2.h>
#include <type_traits>

struct TokenPassData {
    TokenList * token_list = nullptr;
    TokenStream * token_stream = nullptr;
    MicroCpu2 * current_cpu = nullptr;
};

struct MatchData : TokenPassData {
    std::shared_ptr<Token> start;
    std::shared_ptr<Token> end;
    
    TokenList list;
    
    bool matched = false;
    bool execute_actions = true;
    
    inline void reset_match_data() {
        start.reset();
        end.reset();
        list = std::move(TokenList());
        matched = false;
        execute_actions = true;
    }
    
    inline MatchData() { reset_match_data(); token_list = &list; }
    inline virtual ~MatchData() {}
};

struct TokenPass {
    inline virtual void run(TokenPassData & data) {}
    inline virtual ~TokenPass() {}
};

struct Pass : TokenPass {

    // rewriting can be done by using a "read index" and a "write index"
    // in order to keep track of where we are "reading from" and where we are "writing to"
    //
    
    // BACKTRACKING ...
    //
    // this can be implemented via a save/restore stack
    //
    // we save the stack, push a rule to be executed after the current rule, then pop if the rule fails to match
    //
    //
    
    TokenPassData * data;

    typedef std::function<void(MatchData&local)> Action;
    Action default_action;
    
    inline Pass(Action a = [](MatchData&){}) : default_action(a) {}
    
    inline virtual void match(MatchData & m) {}
    
    inline virtual void onRun(MatchData & x) {
        match(x);
    }

    inline void run(MatchData & x) {
        data = static_cast<TokenPassData*>(&x);
        onRun(x);
    }

    inline void run(TokenPassData & x) override final {
        run(*static_cast<MatchData*>(static_cast<void*>(&x)));
    }
    
    inline TokenState save() {
        return data->token_stream->save();
    }
    
    inline void load(const TokenState & s) {
        data->token_stream->load(s);
    }

    inline std::shared_ptr<Token> next() {
        return data->token_stream->pull_token();
    }
    
    inline void after(MicroCpu2::InstructionList * list) {
        list->after([this](void * user_data) mutable {
            run(*static_cast<TokenPassData*>(user_data));
        });
    }
};

struct SinglePass : Pass {
    inline SinglePass(Action a = [](MatchData&){}) : Pass(a) {}
    inline void onRun(MatchData & x) override final { Pass::onRun(x); }
};

struct CustomPass : Pass {
    inline CustomPass(Action a = [](MatchData&){}) : Pass(a) {}
    inline void onRun(MatchData & x) override { Pass::onRun(x); }
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
    inline void onRun(MatchData & user_data) override { f(user_data); };
};

struct Success : SinglePass {
    inline Success(Action a = [](MatchData&){}) : SinglePass(a) {}
    inline void match(MatchData & m) override {
        m.matched = true;
        if (m.execute_actions) {
            MatchData local;
            default_action(local);
        }
    }
};

struct Failure : SinglePass {
    inline Failure(Action a = [](MatchData&){}) : SinglePass(a) {}
    inline void match(MatchData & m) override {
        m.matched = false;
        if (m.execute_actions) {
            MatchData local;
            default_action(local);
        }
    }
};

// for debugging / informational
//
struct Echo : SinglePass {
    const char * msg;
    inline Echo(const char * msg) : msg(msg) {}
    inline void match(MatchData & m) override {
        m.matched = true;
        if (m.execute_actions) {
            printf("%s\n", msg);
            MatchData local;
            default_action(local);
        }
    }
};

struct Any : SinglePass {
    inline Any(Action a = [](MatchData&){}) : SinglePass(a) {}
    inline void match(MatchData & m) override {
        MatchData local;
        auto s = save();
        local.start = next();
        local.end = local.start;
        if (!local.start->is_eof()) {
            m.matched = true;
            local.token_list->push_token(local.end);
            if (m.execute_actions) default_action(local);
            m.token_list->token_list.insert(m.token_list->token_list.end(), local.token_list->token_list.begin(), local.token_list->token_list.end());
        } else {
            load(s);
            m.matched = false;
        }
    }
};

struct EndOfFile : SinglePass {
    inline EndOfFile(Action a = [](MatchData&){}) : SinglePass(a) {}
    inline void match(MatchData & m) override {
        MatchData local;
        auto s = save();
        local.start = next();
        local.end = local.start;
        if (local.start->is_eof()) {
            m.matched = true;
            local.token_list->push_token(local.end);
            if (m.execute_actions) default_action(local);
            m.token_list->token_list.insert(m.token_list->token_list.end(), local.token_list->token_list.begin(), local.token_list->token_list.end());
        } else {
            load(s);
            m.matched = false;
        }
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
                m.matched = true;
                local.token_list->push_token(local.end);
                if (m.execute_actions) default_action(local);
                m.token_list->token_list.insert(m.token_list->token_list.end(), local.token_list->token_list.begin(), local.token_list->token_list.end());
                return;
            }
        }
        load(s);
        m.matched = false;
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
                    m.matched = true;
                    local.token_list->push_token(local.end);
                    if (m.execute_actions) default_action(local);
                    m.token_list->token_list.insert(m.token_list->token_list.end(), local.token_list->token_list.begin(), local.token_list->token_list.end());
                    return;
                }
                local.token_list->push_token(local.end);
                local.end = next();
                i++;
            }
        }
        load(s);
        m.matched = false;
        return;
    }
};

struct Range : SinglePass {
    std::vector<char> range;
    
    inline Range(const std::initializer_list<char> & low_high, Action a = [](MatchData&){}) : SinglePass(a) {
        for(const char & ch : low_high)
            this->range.emplace_back(ch);
    }

    inline void match(MatchData & m) override {
        auto s = save();
        MatchData local;
        local.start = next();
        local.end = local.start;
        size_t e = range.size();
        bool end_of_ranges = false;
        TokenState last_state;
        if (e != 0) {
            size_t i = 0;
            while (!local.end->is_eof()) {
                char ch = local.end->as<ByteToken>().byte;
                // see if we are in range
                while (true) {
                    char low = range[i];
                    if (ch < low) {
                        // we are not in range, see if we have another range
                        i += 2;
                        if (i >= e) {
                            // we have no more ranges
                            end_of_ranges = true;
                            break;
                        }
                        // we have more ranges, try them
                        continue;
                    }
                    // we are in range, see if we have an upper range
                    i++;
                    if (i < e) {
                        // we have an upper range, see if we are in range
                        char high = range[i];
                        if (ch > high) {
                            // we are not in high range, but we are in low range
                            // eg,  ch == 6, low == 2 hi == 4
                            // see if we have more ranges
                            i += 2;
                            if (i >= e) {
                                // we have no more ranges
                                end_of_ranges = true;
                                break;
                            }
                            // we have more ranges, try them
                            continue;
                        }
                    }
                    // we are in range, look at next character
                    i = 0;
                    local.matched = true;
                    local.token_list->push_token(local.end);
                    local.end = next();
                    last_state = local.end->state;
                    break;
                }
                if (end_of_ranges) {
                    break;
                }
            }
            // we reached EOF
        }
        if (local.matched) {
            m.matched = true;

            // the token state returned by next() can be used to undo that specific next()
            // such that the following next() will return the same token
            //
            load(last_state);

            if (m.execute_actions) default_action(local);
            m.token_list->token_list.insert(m.token_list->token_list.end(), local.token_list->token_list.begin(), local.token_list->token_list.end());
        } else {
            // we failed to find any ranges at all
            load(s);
            m.matched = false;
        }
        return;
    }
};

// we now have access to the cpu

inline MicroCpu2::InstructionList * pushMatchData(MicroCpu2 * cpu) {
    MicroCpu2::InstructionList * list = new MicroCpu2::InstructionList();
    MatchData * m = new MatchData();
    list->insert_push_context_after(
        new MicroCpu2::Context(m, [](void*p){ delete static_cast<MatchData*>(p);}),
        [m](MicroCpu2::Context*context){
            MatchData * m1 = static_cast<MatchData*>(m);
            MatchData * m2 = static_cast<MatchData*>(context->user_data);
            m1->execute_actions = m2->execute_actions;
            m1->token_stream = m2->token_stream;
            m1->current_cpu = m2->current_cpu;
        }
    );
    cpu->push_instruction_list(list);
    return list;
}

inline MicroCpu2::InstructionList * pushMatchData(MicroCpu2 * cpu, bool execute_actions) {
    MicroCpu2::InstructionList * list = new MicroCpu2::InstructionList();
    MatchData * m = new MatchData();
    list->insert_push_context_after(
        new MicroCpu2::Context(m, [](void*p){ delete static_cast<MatchData*>(p);}),
        [m, execute_actions](MicroCpu2::Context*context){
            MatchData * m1 = static_cast<MatchData*>(m);
            MatchData * m2 = static_cast<MatchData*>(context->user_data);
            m1->execute_actions = execute_actions;
            m1->token_stream = m2->token_stream;
            m1->current_cpu = m2->current_cpu;
        }
    );
    cpu->push_instruction_list(list);
    return list;
}

inline void popMatchData(MicroCpu2::InstructionList * list) {
    list->insert_pop_context_after();
    list->insert_pop_instruction_list_after([](MicroCpu2::InstructionList*list){delete list;});
}

inline void popMatchData(MicroCpu2::InstructionList* list, const std::function<void(MatchData*,MatchData*)> & on_pop__current__old) {
    list->insert_pop_context_after([on_pop__current__old](MicroCpu2::Context* old_context) {
        on_pop__current__old(static_cast<MatchData*>(static_cast<MatchData*>(old_context->user_data)->current_cpu->get_current_context()->user_data), static_cast<MatchData*>(old_context->user_data));
    });
    list->insert_pop_instruction_list_after([](MicroCpu2::InstructionList*list){delete list;});
}

struct Or : CustomPass {
    
    private:
    std::vector<std::shared_ptr<Pass>> passes;
    
    public:
    
    inline Or(const std::initializer_list<Pass*> & passes, Action a = [](MatchData&){}) : CustomPass(a) {
        for(Pass* p : passes)
            this->passes.emplace_back(p);
    }

    inline void onRun(MatchData & x) override {
        
        // the number of passes cannot change during execution
        //
        if (passes.size() == 0) return;

        auto list = pushMatchData(x.current_cpu);
        list->after([=](void*user_data) {
            MatchData & x = *static_cast<MatchData*>(user_data);
            
            size_t * e = new size_t[2];
            e[0] = passes.size();
            e[1] = 0;

            auto saved = save();
            
            auto list_1 = pushMatchData(x.current_cpu);

            list_1->after([=](void*user_data) {
                MatchData & x = *static_cast<MatchData*>(user_data);
                x.matched = false;
                passes[e[1]]->run(x);
            });
            
            // instruction 0 is a context push
            list_1->insert_absolute_conditional_jump_after(1, [=](void*user_data){
                if(static_cast<MatchData*>(user_data)->matched) {
                    delete[] e;
                    MatchData * x = static_cast<MatchData*>(user_data);
                    if (x->execute_actions) default_action(*x);
                    return false;
                } else if (e[1] == e[0]-1) {
                    delete[] e;
                    load(saved);
                    return false;
                }
                e[1]++;
                return true;
            });
            popMatchData(list_1, [=](MatchData*current, MatchData*old) {
                if (old->matched) {
                    current->matched = true;
                    if (old->token_list->token_list.size() != 0) {
                        current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                    }
                }
            });
        });
        popMatchData(list, [=](MatchData*current, MatchData*old) {
            if (old->matched) {
                current->matched = true;
                if (old->token_list->token_list.size() != 0) {
                    current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                }
            }
        });
    }

};

struct Sequence : CustomPass {
    
    private:
    std::vector<std::shared_ptr<Pass>> passes;
    
    public:
    
    inline Sequence(const std::initializer_list<Pass*> & passes, Action a = [](MatchData&){}) : CustomPass(a) {
        for(Pass* p : passes)
            this->passes.emplace_back(p);
    }
    
    // https://gist.github.com/ZLangJIT/c8c25a3d6280d7a9fbbab8de26b73acc

    inline void onRun(MatchData & x) override {
        
        // the number of passes cannot change during execution
        //
        if (passes.size() == 0) return;

        auto list = pushMatchData(x.current_cpu);
        list->after([=](void*user_data) {
            MatchData & x = *static_cast<MatchData*>(user_data);
            
            size_t * e = new size_t[2];
            e[0] = passes.size();
            e[1] = 0;

            auto saved = save();
            
            auto list_1 = pushMatchData(x.current_cpu);

            list_1->after([=](void*user_data) {
                MatchData & x = *static_cast<MatchData*>(user_data);
                x.matched = false;
                passes[e[1]]->run(x);
            });
            
            // instruction 0 is a context push
            list_1->insert_absolute_conditional_jump_after(1, [=](void*user_data){
                if(!static_cast<MatchData*>(user_data)->matched) {
                    delete[] e;
                    load(saved);
                    return false;
                } else if (e[1] == e[0]-1) {
                    delete[] e;
                    MatchData * x = static_cast<MatchData*>(user_data);
                    if (x->execute_actions) default_action(*x);
                    return false;
                }
                e[1]++;
                return true;
            });
            popMatchData(list_1, [=](MatchData*current, MatchData*old) {
                if (old->matched) {
                    current->matched = true;
                    if (old->token_list->token_list.size() != 0) {
                        current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                    }
                }
            });
        });
        popMatchData(list, [=](MatchData*current, MatchData*old) {
            if (old->matched) {
                current->matched = true;
                if (old->token_list->token_list.size() != 0) {
                    current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                }
            }
        });
    }

};

struct Optional : CustomPass {
    
    private:
    std::shared_ptr<Pass> pass;
    
    public:
    
    inline Optional(Pass* pass, Action a = [](MatchData&){}) : pass(pass), CustomPass(a) {}

    inline void onRun(MatchData & x) override {
        
        auto list = pushMatchData(x.current_cpu);
        list->after([=](void*user_data) {
            MatchData & x = *static_cast<MatchData*>(user_data);
            
            auto saved = save();
            
            auto list_1 = pushMatchData(x.current_cpu);

            list_1->after([=](void*user_data) {
                MatchData & x = *static_cast<MatchData*>(user_data);
                x.matched = false;
                pass->run(x);
            });
            
            list_1->after([=](void*user_data){
                MatchData & x = *static_cast<MatchData*>(user_data);
                if(x.matched) {
                    if (x.execute_actions) default_action(x);
                } else {
                    load(saved);
                }
            });
            popMatchData(list_1, [=](MatchData*current, MatchData*old) {
                current->matched = true;
                if (old->token_list->token_list.size() != 0) {
                    current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                }
            });
        });
        popMatchData(list, [=](MatchData*current, MatchData*old) {
            current->matched = true;
            if (old->token_list->token_list.size() != 0) {
                current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
            }
        });
    }
};

struct At : CustomPass {
    
    private:
    std::shared_ptr<Pass> pass;
    
    public:
    
    inline At(Pass* pass, Action a = [](MatchData&){}) : pass(pass), CustomPass(a) {}

    inline void onRun(MatchData & x) override {
        
        auto list = pushMatchData(x.current_cpu);
        list->after([=](void*user_data) {
            MatchData & x = *static_cast<MatchData*>(user_data);
            
            auto saved = save();
            
            auto list_1 = pushMatchData(x.current_cpu, false);

            list_1->after([=](void*user_data) {
                MatchData & x = *static_cast<MatchData*>(user_data);
                x.matched = false;
                pass->run(x);
            });
            
            list_1->after([=](void*user_data){
                MatchData & x = *static_cast<MatchData*>(user_data);
                if(x.matched) {
                    if (x.execute_actions) default_action(x);
                    load(saved);
                }
            });
            popMatchData(list_1, [=](MatchData*current, MatchData*old) {
                if (old->matched) {
                    current->matched = true;
                    if (old->token_list->token_list.size() != 0) {
                        current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                    }
                }
            });
        });
        popMatchData(list, [=](MatchData*current, MatchData*old) {
            if (old->matched) {
                current->matched = true;
                if (old->token_list->token_list.size() != 0) {
                    current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                }
            }
        });
    }
};

struct Until_At : CustomPass {
    
    private:
    std::shared_ptr<Pass> pass;
    std::shared_ptr<Pass> optional_pass;
    bool has_opt = false;
    
    public:
    
    inline Until_At(Pass* pass, Action a = [](MatchData&){}) : pass(pass), CustomPass(a) {}
    inline Until_At(Pass* pass, Pass* optional_pass, Action a = [](MatchData&){}) : pass(pass), optional_pass(optional_pass), has_opt(true), CustomPass(a) {}

    inline void onRun(MatchData & x) override {
        
        auto list = pushMatchData(x.current_cpu);
        list->after([=](void*user_data) {
            MatchData & x = *static_cast<MatchData*>(user_data);
            
            auto saved = save();
            
            TokenState * last = new TokenState();
            TokenList * last_tk = new TokenList();

            auto list_1 = pushMatchData(x.current_cpu);

            list_1->after([=](void*user_data) {
                MatchData & x = *static_cast<MatchData*>(user_data);
                *last = save();
                *last_tk = *x.token_list;
                x.matched = false;
                pass->run(x);
            });
            
            if (has_opt) {
                // if we match then skip the opt pass
                //
                list_1->insert_relative_conditional_jump_after(3, true, [=](void*user_data){
                    MatchData & x = *static_cast<MatchData*>(user_data);
                    if(x.matched) {
                        load(*last);
                        delete last;
                        x.token_list->token_list = std::move(last_tk->token_list);
                        if (x.execute_actions) default_action(x);
                        return true;
                    }
                    return false;
                });

                // if we dont match then do the opt pass then loop back
                //
                list_1->after([=](void*user_data){
                    MatchData & x = *static_cast<MatchData*>(user_data);
                    optional_pass->run(x);
                    return false;
                });
                // seperate instruction here so opt pass can run
                // if we did a conditional jump then the opt pass wont run
                //
                // instruction 0 is a context push
                //
                list_1->insert_absolute_jump_after(1);
            } else {
                // we have no opt pass
              
                // instruction 0 is a context push
                //
                list_1->insert_absolute_conditional_jump_after(1, [=](void*user_data){
                    MatchData & x = *static_cast<MatchData*>(user_data);
                    if(x.matched) {
                        load(*last);
                        delete last;
                        if (x.execute_actions) default_action(x);
                        return false;
                    }
                    x.token_list->push_token(next());
                    return true;
                });
            }
            popMatchData(list_1, [=](MatchData*current, MatchData*old) {
                delete last_tk;
                if (old->matched) {
                    current->matched = true;
                    if (old->token_list->token_list.size() != 0) {
                        current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                    }
                }
            });
        });
        popMatchData(list, [=](MatchData*current, MatchData*old) {
            if (old->matched) {
                current->matched = true;
                if (old->token_list->token_list.size() != 0) {
                    current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                }
            }
        });
    }

};

struct OneOrMore : CustomPass {
    
    private:
    std::shared_ptr<Pass> pass;

    public:
    
    inline OneOrMore(Pass* pass, Action a = [](MatchData&){}) : pass(pass), CustomPass(a) {}

    inline void onRun(MatchData & x) override {
        
        auto list = pushMatchData(x.current_cpu);
        list->after([=](void*user_data) {
            MatchData & x = *static_cast<MatchData*>(user_data);
            
            bool * has_one_match = new bool();
            *has_one_match = false;
            
            auto saved = save();

            auto list_1 = pushMatchData(x.current_cpu);

            list_1->after([=](void*user_data) {
                MatchData & x = *static_cast<MatchData*>(user_data);
                x.matched = false;
                pass->run(x);
            });
            
            // instruction 0 is a context push
            //
            list_1->insert_absolute_conditional_jump_after(1, [=](void*user_data){
                    MatchData & x = *static_cast<MatchData*>(user_data);
                if(x.matched) {
                    *has_one_match = true;
                    return true;
                } else {
                    if (x.execute_actions && *has_one_match) default_action(x);
                    return false;
                }
            });
            popMatchData(list_1, [=](MatchData*current, MatchData*old) {
                if (*has_one_match) {
                    current->matched = true;
                    if (old->token_list->token_list.size() != 0) {
                        current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                    }
                }
                delete has_one_match;
            });
        });
        popMatchData(list, [=](MatchData*current, MatchData*old) {
            if (old->matched) {
                current->matched = true;
                if (old->token_list->token_list.size() != 0) {
                    current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                }
            }
        });
    }
};

struct ZeroOrMore : CustomPass {
    
    private:
    std::shared_ptr<Pass> pass;

    public:
    
    inline ZeroOrMore(Pass* pass, Action a = [](MatchData&){}) : pass(pass), CustomPass(a) {}

    inline void onRun(MatchData & x) override {
        
        auto list = pushMatchData(x.current_cpu);
        list->after([=](void*user_data) {
            MatchData & x = *static_cast<MatchData*>(user_data);
            
            auto saved = save();

            auto list_1 = pushMatchData(x.current_cpu);

            list_1->after([=](void*user_data) {
                MatchData & x = *static_cast<MatchData*>(user_data);
                x.matched = false;
                pass->run(x);
            });
            
            // instruction 0 is a context push
            //
            list_1->insert_absolute_conditional_jump_after(1, [=](void*user_data){
                MatchData & x = *static_cast<MatchData*>(user_data);
                if(x.matched) {
                    return true;
                } else {
                    if (x.execute_actions) default_action(x);
                    return false;
                }
            });
            popMatchData(list_1, [=](MatchData*current, MatchData*old) {
                current->matched = true;
                if (old->token_list->token_list.size() != 0) {
                    current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                }
            });
        });
        popMatchData(list, [=](MatchData*current, MatchData*old) {
            if (old->matched) {
                current->matched = true;
                if (old->token_list->token_list.size() != 0) {
                    current->token_list->token_list.insert(current->token_list->token_list.end(), old->token_list->token_list.begin(), old->token_list->token_list.end());
                }
            }
        });
    }
};

inline void pushParseContext(MicroCpu2::InstructionList * list) {
    MatchData * m = new MatchData();
    list->insert_push_context_after(
        new MicroCpu2::Context(m, [](void*p){ delete static_cast<MatchData*>(p);}),
        [m](MicroCpu2::Context*context){
            *static_cast<TokenPassData*>(m) = *static_cast<TokenPassData*>(context->user_data);
        }
    );
}

inline void popParseContext(MicroCpu2::InstructionList * list) {
    list->insert_pop_context_after();
    list->insert_pop_instruction_list_after();
}

#endif