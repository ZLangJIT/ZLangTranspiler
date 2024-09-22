#include <tuple>
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <stack>
#include <deque>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <stream.h>
#include <math.h>
#include <tcc/libtcc.h>

class tcc_jit {
  static void handle_error(void *opaque, const char *msg) {
      fprintf(static_cast<FILE*>(opaque), "%s\n", msg);
  }
  
  std::shared_ptr<TCCState> tcc_state;
  std::string binds;
  
  public:

  class Obj {
      friend tcc_jit;
      std::string code;

      public:
      void print(const std::string str) {
        code += str;
      }
    
      void println(const std::string str) {
        code += str;
        code += "\n";
      }
  };
  
  std::vector<std::shared_ptr<Obj>> objects;
  
  std::shared_ptr<Obj> add_obj() {
    return objects.emplace_back(new Obj());
  }
  
  bool compile(bool include_default_defines = true) {
    tcc_state.reset();
    TCCState * state = tcc_new_with_defines(include_default_defines);
    if (!state) {
      std::cout << "failed to create a new tcc state" << std::endl;
      return false;
    }
    tcc_state.reset(state, [](TCCState*state){tcc_delete(state);});
    tcc_set_error_func(state, stderr, handle_error);
    tcc_set_output_type(state, TCC_OUTPUT_MEMORY);
    for (auto & o : options) {
      tcc_set_options(state, o.c_str());
    }
    for (auto & obj : objects) {
        std::string code = this->binds + "\n" + obj->code + "\n";
        auto r = tcc_compile_string(state, code.c_str());
        if (r != 0) {
          std::cout << "failed to compile code: tcc_compile_string() returned " << std::to_string(r) << std::endl;
          tcc_state.reset();
          return false;
        }
    }
    return true;
  }
  
  std::vector<std::pair<void*, std::string>> bind_map;
  std::vector<std::string> options;

  int operator()() {
    TCCState * s = tcc_state.get();
    if (s == nullptr) {
      std::cout << "cannot execute code that has not yet been compiled" << std::endl;
      return -1;
    }
    for (auto & map : bind_map) {
      if (map.second == "N_CRASH") continue;
      std::cout << "binding symbol [" << map.second << "] ..." << std::endl;
      if (tcc_add_symbol(s, map.second.c_str(), map.first) != 0) {
        std::cout << "warning: failed to bind symbol [" << map.second << "]" << std::endl;
      }
    }
    std::cout << "binded symbols" << std::endl;
    
    std::cout << "relocating symbols..." << std::endl;
    auto r2 = tcc_relocate(s, TCC_RELOCATE_AUTO);
    if (r2 != 0) {
      std::cout << "failed to relocate code: tcc_relocate() returned " << std::to_string(r2) << std::endl;
      return -1;
    }
    std::cout << "relocated symbols" << std::endl;
    auto m = ((int(*)())tcc_get_symbol(s, "main"));
    if (m == nullptr) {
      std::cout << "failed to find symbol [main] in code" << std::endl;
      return -1;
    }
    return m();
  }
  
  template <typename T>
  void bind(T symbol_or_address, const char * name) {
    bind_map.emplace_back((void*)symbol_or_address, name);
  }
  
  void opt(const char * tcc_opt) {
    options.emplace_back(tcc_opt);
  }
};

void print(const char * s) {
  std::cout << s << std::endl << std::flush;
}

bool test_syntax(const char * syntax) {
  tcc_jit o;
  auto obj = o.add_obj();
  obj->println(syntax);
  return o.compile(false);
}

bool test_class() {
  return test_syntax("struct foo {};")
         && test_syntax("class foo {};")
         && test_syntax("class foo { int bar_variable; };")
         && test_syntax("int bar_func(); class foo { int bar_variable; int bar_func(); };")
         && test_syntax("int bar_func(); class foo { int bar_variable; int bar_func(); int bar_func() { return 0; } };")
         && test_syntax("int bar_func() { return 5; } class foo { int bar_variable; int bar_func() { return 5; } };")
         && test_syntax("class foo { int bar_func() { return 5; } }; void do_foo() { struct foo f; f.bar_func(); }")
         && test_syntax("int bar_func() { return 2; } class foo { int bar_func() { return 5; } }; void do_foo() { struct foo f; f.bar_func(); }")
         && test_syntax("class x { void a() {} void a(int b) {} }; void a() {} void a(int b) {}")
   ;
}

void tests() {
  if (
    !(
      test_class()
    )
  ) {
    exit(1);
  }
}

int main(int argc, char **argv) {
  if (false) {
    tests();
  }
  if (false) {
    tcc_jit o;
    auto obj = o.add_obj();
    obj->println("void print(const char*); class foo { void b() { print(\"foo::b\"); } }; int main() { print(\"hi\"); struct foo f; f.b(); return 0; }");
    o.compile();
    o.bind(print, "print");
    o();
  }
  if (false) {
    tcc_jit o;
    o.add_obj()->println("void print(const char*); void b() { print(\"::b\"); } class foo { int x2; int x4; void b() { print(\"foo::b\"); } int x; }; void c() { print(\"::c\"); } int main() { print(\"hi\"); b(); c(); struct foo f; f.b(); c(); f.x = 5; f.x2 = 6; f.x4 = 7; b(); c(); f.b(); c(); return 0; }");
    o.compile();
    o.bind(print, "print");
    o();
  }
  if (false) {
    tcc_jit o;
    o.add_obj()->println("void print(const char*); void b() { print(\"::b 1\"); }");
    o.add_obj()->println("void print(const char*); void b() { print(\"::b 2\"); }");
    o.add_obj()->println("void print(const char*); void b(); int main() { b(); }");
    o.compile();
    o.bind(print, "print");
    o();
  }
  if (false) {
    tcc_jit o;
    o.add_obj()->println("void print(const char*); class foo { void b() { print(\"::b\"); } };");
    //o.add_obj()->println("void print(const char*); class foo { void b() { print(\"::b\"); } };");
    o.add_obj()->println("void print(const char*); class foo { void b(); }; int main() { struct foo f; f.b(); }");
    o.compile();
    o.bind(print, "print");
    o();
  }
  if (true) {
    tcc_jit o;
    o.add_obj()->println("void print(const char*); class foo1 { void bar84(float y) { print(\"foo1::bar84\"); } void bar88(int x) { print(\"foo1::bar88\"); } void bar88() { print(\"foo1::bar88 void\"); } }; ");
    o.add_obj()->println("void print(const char*); class foo1 { void bar84(float y); void bar88(int x); void bar88(); }; void baz() { struct foo1 f; f.bar84(4.7f); f.bar88(5); f.bar88(); } int main() { baz(); return 0; }");
    o.compile(false); // no default defines
    o.bind(print, "print");
    o();
  }
  return 0;
}

/*
tccgen.h notes

static void struct_decl(CType *type, int u)

gen.cpp : 4317
    - struct_decl - handle 'function(...) {}' body in struct
                    if (tok == '{') {
                      skip(',');
                      continue;
                    }
                    skip(',');
                    
// gen.cpp : 7819 - possible vars required for function body handling

#ifdef BF_DEBUG
            printf("FIX field %s : load byte-wise\n",
                 get_tok_str(f->v & ~SYM_FIELD, NULL));
#endif

*/