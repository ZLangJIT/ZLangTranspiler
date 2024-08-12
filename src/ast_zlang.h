#ifndef ZLANG_AST_H
#define ZLANG_AST_H

#include <token_combinator.h>

struct ast_zlang {
    
    std::unique_ptr<TokenList> token_list;
    std::unique_ptr<TokenPassManager> pm;
    
    inline ast_zlang() {}
    
    inline void reset() {
        token_list.reset(new TokenList());
        pm.reset(new TokenPassManager());
        auto context = pushParseContext(*pm);
        pm->after(
            new Or({
                new Echo("0"),
                new Or({new Echo("1"), new Echo("2")}),
                new Or({new Echo("3"), new Echo("4")}),
                new Echo("5"),
                new Echo("6"),
                new Or({new Echo("7"), new Echo("8")})
                //new Or(new String("a// pineapple"), new Char('b'))
                //,
                // new Char('a'),
                // new Char('c'),
                // new String("//"),
                // new Char('d'),
                // new Range('a','z','A','Z', ' ')
            }, [](MatchData&){ puts("RULE MATCHES"); })
        );
        popParseContext(*pm, context);
    }

    inline void parse(TokenStream & ts) {
        reset();
        pm->runFromStart(*token_list, ts);
        token_list->print();
    }
};

#endif