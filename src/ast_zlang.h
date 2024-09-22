#ifndef ZLANG_AST_H
#define ZLANG_AST_H

#include <token_combinator.h>

struct ast_zlang {
    
    inline ast_zlang() {}
    
    struct Tokens {
        static inline Tokens & get() {
            static Tokens id;
            return id;
        }

        const std::unique_ptr<uint8_t> comment { new uint8_t };
        const std::unique_ptr<uint8_t> diagnostic { new uint8_t };

        struct CommentToken : SpanToken {
            inline CommentToken() {
                token_id = Tokens::get().comment.get();
            }
            
            inline void print() override {
                print_file_marker();
                auto str = extract_string();
                printf(": CommentToken \"%s\"\n", str.c_str());
            }
        };

        struct DiagnosticToken : SpanToken {
            const char * msg;
            
            inline DiagnosticToken(const char * msg) : msg(msg) {
                token_id = Tokens::get().diagnostic.get();
            }
            
            inline void print() override {
                print_file_marker();
                auto str = extract_string();
                printf(": DiagnosticToken \"%s\" [ msg = \"%s\" ]\n", str.c_str(), msg);
            }
        };
    } ids;
    
    inline auto comment(Pass::Action a = [](MatchData&){}) {
        return new Or({
            new Sequence({
                new Sequence({
                        new String("//"),
                        new Until_At(new Or({new Char('\n'), new EndOfFile()}))
                    },
                    [](MatchData&x) { (new Tokens::CommentToken())->collapse(*x.token_list); }
                ),
                new Optional(new Char('\n'))
            }),
            new Sequence({
                new Sequence({
                        new String("/*"),
                        new Until_At(new Or({new String("*/"), new EndOfFile()})),
                        new Optional(new String("*/"))
                    },
                    [](MatchData&x) { (new Tokens::CommentToken())->collapse(*x.token_list); }
                ),
            })
        });
    }
    
    inline auto to_diagnostic(const char * msg) {
        return [msg](MatchData&x) {
            (new Tokens::DiagnosticToken(msg))->collapse(*x.token_list);
        };
    }
    
    auto whitespace() {
      return new ZeroOrMore(new Or({
        new Char(' '), new Char('\t'), new Sequence({new Optional(new Char('\r')), new Char('\n')})
      })); 
    }
    
    auto package() {
      return new Sequence({
        new String("package"),
      });
    }

    inline void parse(TokenStream & ts) {
        MicroCpu2 cpu;
        MicroCpu2::InstructionList instruction_list;
        pushParseContext(&instruction_list);
        auto seq = Sequence({
            new Echo("parsing..."),
            new Until_At(
                new EndOfFile(),
                new Or({
                    //new Range({'a', 'z', 'A', 'Z'}, [](auto&x){(new SpanToken())->collapse(*x.token_list);}),
                    new OneOrMore(comment()),
                    new Char('\n'), new Char(' '), new Char('\t'), new Char(';'),
                    
                    // skip any tokens which are not valid
                    //
                    new Any(to_diagnostic("invalid token"))
                })
            ),
            new EndOfFile(),
            new Echo("parsing complete")
        });
        seq.after(&instruction_list);
        popParseContext(&instruction_list);

        TokenList token_list;
        TokenPassData data;

        data.token_list = &token_list;
        data.token_stream = &ts;
        data.current_cpu = &cpu;

        cpu.exe(&instruction_list, &data);

        token_list.print();
    }
};

#endif