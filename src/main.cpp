#include "ast_zlang.h"

int main(int argc, const char ** argv) {
    Stream str;
    if (!str.open("bootstrap.z")) return -1;
    
    TokenStream ts;
    ts.stream = &str;
    
    ast_zlang z;
    z.parse(ts);

    return 0;
}
