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
#include <Rules_Extra.h>

const char * zlang_c_compiler;
const char * zlang_cxx_compiler;

extern "C" {
  void zlang_create_no_link();
  void zlang_create_static_library(const char * name);
  void zlang_create_shared_library(const char * name);
  void zlang_create_exe(const char * name);
  void zlang_create_c_file(const char * name);
  void zlang_create_cxx_file(const char * name);
  void zlang_create_transpile_file(const char * name);
  void zlang_finalize();
  bool zlang_push_input(const char * path);
  int zlang_get_input_c();
  void zlang_write(const char * str, size_t len);
}

struct zlang_Input {
  std::string input;
  const char * input_c = "";
  
  zlang_Input() {}

  zlang_Input(const zlang_Input & x) {
    input = x.input;
    input_c = input.c_str();
  }
  
  zlang_Input(zlang_Input && x) {
    input = std::move(x.input);
    input_c = input.c_str();
  }

  zlang_Input & operator=(const zlang_Input & x) {
    input = x.input;
    input_c = input.c_str();
    return *this;
  }

  zlang_Input & operator=(zlang_Input && x) {
    input = std::move(x.input);
    input_c = input.c_str();
    return *this;
  }

  bool read_file(const char * path) {
    std::ifstream t(path, std::ios::binary);
    input = std::move(std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>()));
    input_c = input.c_str();
    return *input_c != '\0';
  }

  int get_input_c() {
      return *input_c == '\0' ? -1 : *input_c++;
  }
};

std::ofstream zlang_output;

void zlang_write(const char * str, size_t len) {
  zlang_output.write(str, len);
  zlang_output.flush();
}

void zlang_write(const char * str) { zlang_write(str, strlen(str)); }
void zlang_write(const std::string & str) { zlang_write(str.c_str(), str.length()); }

std::vector<zlang_Input> zlang_inputs;
size_t zlang_current = -1;

bool zlang_push_input(const char * path) {
    zlang_Input i;
    if (i.read_file(path)) {
      zlang_inputs.emplace_back(std::move(i));
      zlang_current = zlang_inputs.size()-1;
      return true;
    }
    return false;
}

void zlang_pop_input() {
    zlang_inputs.pop_back();
    zlang_current = zlang_inputs.size()-1;
}

int zlang_get_input_c() {
    if (zlang_current == -1) return -1;
    int ret = zlang_inputs[zlang_current].get_input_c();
    while (ret == -1) {
        zlang_pop_input();
        if (zlang_current == -1) return -1;
        ret = zlang_inputs[zlang_current].get_input_c();
    }
    return ret;
}

struct zlang_CMD {
    std::string name, full_name, type_string;
    bool is_exe;
    bool is_shared_library;
    bool is_static_library;
    bool is_c_object;
    bool is_cxx_object;
    bool is_transpile_object;
    bool no_link;
    bool built;
    std::string transpile_command;
    std::vector<zlang_CMD> file_list;
    std::vector<std::string> include_list;
};

std::vector<zlang_CMD> zlang_command_list;
size_t zlang_current_command;

void zlang_create_no_link() {
    if (zlang_command_list.size() == 0) {
      zlang_command_list.emplace_back(zlang_CMD());
      zlang_command_list.back().name = "no_link";
      zlang_command_list.back().full_name = "no_link";
      zlang_command_list.back().no_link = true;
      zlang_command_list.back().type_string = "no_link";
    }
    zlang_current_command = 0;
}

void zlang_create_exe_(const std::string name) {
    for (size_t i = 0; i < zlang_command_list.size(); i++) {
      if (!zlang_command_list[i].no_link && name == zlang_command_list[i].name) {
        printf("switching to executable: %s\n", name.c_str());
        zlang_current_command = i;
        return;
      }
    }
    printf("creating executable: %s\n", name.c_str());
    zlang_command_list.emplace_back(zlang_CMD());
    zlang_current_command = zlang_command_list.size()-1;
    zlang_command_list[zlang_current_command].name = name;
    zlang_command_list[zlang_current_command].full_name = name + ".exe";
    zlang_command_list[zlang_current_command].is_exe = true;
    zlang_command_list[zlang_current_command].type_string = "executable";
}

void zlang_create_shared_library_(const std::string name) {
    for (size_t i = 0; i < zlang_command_list.size(); i++) {
      if (!zlang_command_list[i].no_link && name == zlang_command_list[i].name) {
        printf("switching to shared library: %s\n", name.c_str());
        zlang_current_command = i;
        return;
      }
    }
    printf("creating shared library: %s\n", name.c_str());
    zlang_command_list.emplace_back(zlang_CMD());
    zlang_current_command = zlang_command_list.size()-1;
    zlang_command_list[zlang_current_command].name = name;
    zlang_command_list[zlang_current_command].full_name = name + ".so";
    zlang_command_list[zlang_current_command].is_shared_library = true;
    zlang_command_list[zlang_current_command].type_string = "shared_library";
}

void zlang_create_static_library_(const std::string name) {
    for (size_t i = 0; i < zlang_command_list.size(); i++) {
      if (!zlang_command_list[i].no_link && name == zlang_command_list[i].name) {
        printf("switching to static library: %s\n", name.c_str());
        zlang_current_command = i;
        return;
      }
    }
    printf("creating static library: %s\n", name.c_str());
    zlang_command_list.emplace_back(zlang_CMD());
    zlang_current_command = zlang_command_list.size()-1;
    zlang_command_list[zlang_current_command].name = name;
    zlang_command_list[zlang_current_command].full_name = name + ".a";
    zlang_command_list[zlang_current_command].is_static_library = true;
    zlang_command_list[zlang_current_command].type_string = "static_library";
}

void zlang_create_source_file(const std::string name, bool is_c, bool is_cxx) {
    for (size_t i = 0; i < zlang_command_list[zlang_current_command].file_list.size(); i++) {
      if ((zlang_command_list[zlang_current_command].name + "(" + zlang_command_list[zlang_current_command].type_string + "):" + name) == zlang_command_list[zlang_current_command].file_list[i].name) {
        printf("switching to %s file: %s(%s):%s\n", is_c ? "c" : is_cxx ? "c++" : "transpile", zlang_command_list[zlang_current_command].name.c_str(), zlang_command_list[zlang_current_command].type_string.c_str(), name.c_str());
        if (zlang_output.is_open()) {
          zlang_output.flush();
          zlang_output.close();
        }
        zlang_output = std::ofstream(zlang_command_list[zlang_current_command].file_list[i].full_name.c_str(), std::ios::binary);
        return;
      }
    }
    if (zlang_command_list[zlang_current_command].no_link) {
      printf("creating %s file: %s.%s\n", is_c ? "c" : is_cxx ? "c++" : "transpile", name.c_str(), is_c ? "c" : is_cxx ? "cxx" : "transpile");
    } else {
      printf("creating %s file: %s(%s):%s.%s\n", is_c ? "c" : is_cxx ? "c++" : "transpile", zlang_command_list[zlang_current_command].name.c_str(), zlang_command_list[zlang_current_command].type_string.c_str(), name.c_str(), is_c ? "c" : is_cxx ? "cxx" : "transpile");
    }
    zlang_command_list[zlang_current_command].file_list.emplace_back(zlang_CMD());
    zlang_CMD & file = zlang_command_list[zlang_current_command].file_list.back();
    file.name = zlang_command_list[zlang_current_command].name + "(" + zlang_command_list[zlang_current_command].type_string + "):" + name;
    file.full_name = (zlang_command_list[zlang_current_command].no_link ? name : std::string("_gen_") + zlang_command_list[zlang_current_command].name + "__" + zlang_command_list[zlang_current_command].type_string + "__" + name) + "." + (is_c ? "c" : is_cxx ? "cxx" : "transpile");
    file.is_c_object = is_c;
    file.is_cxx_object = is_cxx;
    file.is_transpile_object = !is_c && !is_cxx;
    if (zlang_output.is_open()) {
      zlang_output.flush();
      zlang_output.close();
    }
    zlang_output = std::ofstream(file.full_name.c_str(), std::ios::binary);
}

void zlang_create_static_library(const char * name) { zlang_create_static_library_(name); }
void zlang_create_shared_library(const char * name) { zlang_create_shared_library_(name); }
void zlang_create_exe(const char * name) { zlang_create_exe_(name); }
void zlang_create_c_file(const char * name) { zlang_create_source_file(name, true, false); }
void zlang_create_cxx_file(const char * name) { zlang_create_source_file(name, false, true); }
void zlang_create_transpile_file(const char * name) { zlang_create_source_file(name, false, false); }

bool zlang_build_command(zlang_CMD & cmd) {
  bool contains_cxx_files = false;
  for (auto & file : cmd.file_list) {
    if (file.is_transpile_object) {
      if (!file.built) {
        printf("  building transpile object: %s.%s\n", file.name.c_str(), file.is_c_object ? "c" : "cxx");
        system(file.transpile_command.c_str());
      }
    }
    if (file.is_c_object) {
      if (!file.built) {
        printf("  building c object: %s.o\n", file.name.c_str());
        std::string command = zlang_c_compiler;
        for (auto & s : cmd.include_list) {
          command += " -I " + s;
        }
        command += " -c ";
        command += file.full_name + " ";
        command += "-o " + file.full_name + ".o";
        system(command.c_str());
        file.built = true;
      }
    } else if (file.is_cxx_object) {
      if (!file.built) {
        printf("  building c++ object: %s.o\n", file.name.c_str());
        std::string command = zlang_cxx_compiler;
        for (auto & s : cmd.include_list) {
          command += " -I " + s;
        }
        command += " -c ";
        command += file.full_name + " ";
        command += "-o " + file.full_name + ".o";
        system(command.c_str());
        contains_cxx_files = true;
        file.built = true;
      }
    } else {
      printf("  error: file %s is not a source file\n", file.name.c_str());
      exit(1);
    }
  }
  return contains_cxx_files;
}

void zlang_link_command(zlang_CMD & cmd) {
  if (cmd.built) return;
  bool contains_cxx_files = zlang_build_command(cmd);
  if (cmd.is_static_library) {
    printf("linking static library: %s\n", cmd.name.c_str());
    for (auto & file : cmd.file_list) {
    }
  } else if (cmd.is_shared_library) {
    printf("linking shared library: %s\n", cmd.name.c_str());
    for (auto & file : cmd.file_list) {
    }
  } else {
    printf("linking executable: %s\n", cmd.name.c_str());
    std::string command = contains_cxx_files ? zlang_cxx_compiler : zlang_c_compiler;
    command += " -o ";
    command += cmd.full_name;
    for (auto & file : cmd.file_list) {
      command += " " + file.full_name + ".o";
    }
    system(command.c_str());
  }
  cmd.built = true;
}

void zlang_finalize() {
  if (zlang_output.is_open()) {
    zlang_output.flush();
    zlang_output.close();
    zlang_output = std::move(std::ofstream());
  }
  
  for (auto & cmd : zlang_command_list) {
      if (cmd.is_c_object || cmd.is_cxx_object || cmd.is_transpile_object) {
        printf("error: source file %s is not part of any build\n", cmd.name.c_str());
        exit(1);
      }
  }

  // build all static libraries
  for (auto & cmd : zlang_command_list) {
    if (cmd.is_static_library && cmd.file_list.size() != 0) {
      printf("building static library: %s\n", cmd.name.c_str());
      zlang_link_command(cmd);
    }
  }

  // build all shared libraries
  for (auto & cmd : zlang_command_list) {
    if (cmd.is_shared_library && cmd.file_list.size() != 0) {
      printf("building shared library: %s\n", cmd.name.c_str());
      zlang_link_command(cmd);
    }
  }

  // build all executables
  for (auto & cmd : zlang_command_list) {
    if (cmd.is_exe && cmd.file_list.size() != 0) {
      printf("building executable: %s\n", cmd.name.c_str());
      zlang_link_command(cmd);
    }
  }
}

struct Node {
  bool node_is_variable;
  bool node_is_function;
  std::string node_type;
  std::string node_name;
  std::string node_params;
  std::string node_body;
};

struct {
  std::deque<Node> nodes;
  void push(const Node & n) { nodes.emplace_back(n); }
  Node pull() { auto s = nodes.front(); nodes.pop_front(); return s; }
  bool has_one() { return nodes.size() != 0; }
} nodes;

struct {
  std::deque<std::string> strings;
  
  void push(const std::string & n) { strings.emplace_back(n); }
  std::string pull() { auto s = strings.front(); strings.pop_front(); return s; }
  bool has_one() { return strings.size() != 0; }
} syntax;

using namespace QParse;

enum LEXER_ID {
  LEXER_ID_C_IDENT,
  LEXER_ID_PAREN_OPEN,
  LEXER_ID_PAREN_CLOSE,
  LEXER_ID_BRACE_OPEN,
  LEXER_ID_BRACE_CLOSE,
  LEXER_ID_COMMA,
  LEXER_ID_STATEMENT_SEPERATOR,
  LEXER_ID_DIGIT,
  LEXER_ID_FLOATING_POINT__FLOAT,
  LEXER_ID_FLOATING_POINT__DOUBLE,
  LEXER_ID_OP,
  LEXER_ID_CHARACTER_LITERAL,
  LEXER_ID_STRING_LITERAL
};

inline const char * LEXER_id_to_string(LEXER_ID id) {
  switch(id) {
    case LEXER_ID_STRING_LITERAL: return "string literal";
    case LEXER_ID_CHARACTER_LITERAL: return "character literal";
    case LEXER_ID_OP: return "operator";
    case LEXER_ID_FLOATING_POINT__DOUBLE: return "floating point (double)";
    case LEXER_ID_FLOATING_POINT__FLOAT: return "floating point (float)";
    case LEXER_ID_DIGIT: return "digit";
    case LEXER_ID_STATEMENT_SEPERATOR: return "statement seperator";
    case LEXER_ID_COMMA: return "comma";
    case LEXER_ID_BRACE_CLOSE: return "brace close";
    case LEXER_ID_BRACE_OPEN: return "brace open";
    case LEXER_ID_PAREN_CLOSE: return "paren close";
    case LEXER_ID_PAREN_OPEN: return "paren open";
    case LEXER_ID_C_IDENT: return "c identifier";
    default: return "unknown";
  }
}

struct LEXER_NODE {
  LEXER_ID id;
  int scope;
  QParse::IteratorMatcher::MatchData m;
  std::string * input;
  std::string name;
  std::string str() {
    if (input == nullptr) return "";
    QParse::Iterator i(*input);
    i.setCurrent(m.begin);
    return i.substr(m.begin, m.end);
  }

  inline bool is(const std::string & s) { return str() == s; }
  inline bool is(const char * s) { return str() == s; }
  inline bool is(const LEXER_ID & id) { return this->id == id; }

  void print() {
    std::string indent;
    indent.append(scope*4, ' ');
    std::string msg;
    msg.append(LEXER_id_to_string(id));
    QParse::Iterator i(*input);
    i.name = name;
    i.setCurrent(m.begin);
    msg.append(" [ '");
    msg.append(i.substr(m.begin, m.end));
    msg.append("' ]\n");
    printf("%s%s", indent.c_str(), msg.c_str());
    QParse::Rules::UndoRedo u;
    u.print_error(i, indent.c_str());
  }
  void error(const char * str) {
    QParse::Iterator i(*input);
    i.name = name;
    i.setCurrent(m.begin);
    QParse::Rules::UndoRedo u;
    QParse::Rules::printError(str, i, u);
  }
  void note(const char * str) {
    QParse::Iterator i(*input);
    i.name = name;
    i.setCurrent(m.begin);
    QParse::Rules::UndoRedo u;
    QParse::Rules::printNote(str, i, u);
  }
};

struct CST {
  std::vector<LEXER_NODE> nodes;
  int scope = 1;
  
  void push(LEXER_ID id, QParse::Rules::Input it) {
    LEXER_NODE n;
    n.id = id;
    n.m = it.match;
    n.input = it.iterator.input;
    n.name = it.iterator.name;
    n.scope = scope;
    nodes.emplace_back(n);
  }
  
  void print() {
    printf("CST: [\n");
    for (LEXER_NODE & node : nodes) node.print();
    printf("]\n");
  }
} CST;


auto whitespace(Rules::Action a = Rules::NO_ACTION) {
  return new Rules::ZeroOrMore(new Rules::Or({
    new Rules::Char(' '),
    new Rules::Char('\\'),
    new Rules::Sequence({new Rules::Optional(new Rules::Char('\r')), new Rules::Char('\n')}),
    new Rules::Char('\t'),
    new Rules::Char('\v')
  }), a);
}

auto c_identifier() {
  return new Rules::Sequence({
    new Rules::Or({new Rules::Char('_'), new Rules::Range({'a', 'z', 'A', 'Z'}) }),
    new Rules::ZeroOrMore(new Rules::Or({new Rules::Char('_'), new Rules::Range({'a', 'z', 'A', 'Z', '0', '9'}) }))
  }, [](auto i) {CST.push(LEXER_ID_C_IDENT, i);});
}

auto digit_or_floating_point() {
  return new Rules::Or({
    new Rules::Sequence({
      new Rules::OneOrMore(new Rules::Range({'0', '9'})),
      new Rules::Char('.'),
      new Rules::OneOrMore(new Rules::Range({'0', '9'})),
      new Rules::Char('f')
    }, [](auto i) {CST.push(LEXER_ID_FLOATING_POINT__FLOAT, i);}),
    new Rules::Sequence({
      new Rules::OneOrMore(new Rules::Range({'0', '9'})),
      new Rules::Char('.'),
      new Rules::OneOrMore(new Rules::Range({'0', '9'})),
    }, [](auto i) {CST.push(LEXER_ID_FLOATING_POINT__DOUBLE, i);}),
    new Rules::Sequence({
      new Rules::OneOrMore(new Rules::Range({'0', '9'})),
    }, [](auto i) {CST.push(LEXER_ID_DIGIT, i);}),
  });
}

auto op() {
  return new Rules::Or({
    new Rules::Char('#'),
    new Rules::Char('@'),
    new Rules::Char('$'),
    new Rules::Char('='),
    new Rules::Char(':'),
    new Rules::Char('?'),
    new Rules::Char('<'),
    new Rules::Char('>'),
    new Rules::Char('^'),
    new Rules::Char('|'),
    new Rules::Char('!'),
    new Rules::Char('['),
    new Rules::Char(']'),
    new Rules::Char('.'),
    new Rules::Char('+'),
    new Rules::Char('-'),
    new Rules::Char('*'),
    new Rules::String("->"),
    new Rules::Char('/'),
    new Rules::Char('%'),
    new Rules::Char('&'),
  }, [](auto i) {CST.push(LEXER_ID_OP, i);});
}

auto paren_open() {
  return new Rules::Char('(', [](auto i){CST.push(LEXER_ID_PAREN_OPEN, i);});
}

auto paren_close() {
  return new Rules::Char(')', [](auto i){CST.push(LEXER_ID_PAREN_CLOSE, i);});
}

auto comma() {
  return new Rules::Char(',', [](auto i){CST.push(LEXER_ID_COMMA, i);});
}

auto brace_open() {
  return new Rules::Char('{', [](auto i){CST.push(LEXER_ID_BRACE_OPEN, i); CST.scope++;});
}

auto brace_close() {
  return new Rules::Char('}', [](auto i){CST.scope--; CST.push(LEXER_ID_BRACE_CLOSE, i);});
}

auto statement_end() {
  return new Rules::Char(';', [](auto i){CST.push(LEXER_ID_STATEMENT_SEPERATOR, i);});
}

auto literal_character() {
  return new Rules::Sequence({
    new Rules::Char('\''),
    new Rules::ErrorIfMatch(new Rules::Char('\''), "expected a character"),
    new Rules::Optional(new Rules::Char('\\')),
    new Rules::Any(),
    new Rules::ErrorIfNotMatch(new Rules::Char('\''), "expected a matching single quote ''' (\\')")
  }, [](auto i){CST.push(LEXER_ID_CHARACTER_LITERAL, i);});
}

auto literal_string() {
  return new Rules::Sequence({
    new Rules::Char('"'),
    new Rules::ZeroOrMore(new Rules::Sequence({
      new Rules::NotAt(new Rules::Char('"')),
      new Rules::Optional(new Rules::Char('\\')),
      new Rules::Any()
    })),
    new Rules::ErrorIfNotMatch(new Rules::Char('"'), "expected a matching double quote '\"' (\")")
  }, [](auto i){CST.push(LEXER_ID_STRING_LITERAL, i);});
}

auto preprocessor_angle_include() {
  return new Rules::Sequence({
    new Rules::Char('#'),
    whitespace(),
    new Rules::String("include"),
    whitespace(),
    new Rules::Char('<'),
    new Rules::ZeroOrMore(new Rules::Sequence({
      new Rules::NotAt(new Rules::Char('>')),
      new Rules::Any()
    })),
    new Rules::ErrorIfNotMatch(new Rules::Char('>'), "expected a matching angle '>' (<src>)")
  });
}

auto parse() {
  return new Rules::Sequence({
    new Rules::OneOrMore(
      new Rules::Sequence({
        whitespace(),
        new Rules::Or({
          QParse_Rules_LogTrace(preprocessor_angle_include()),
          QParse_Rules_LogTrace(c_identifier()),
          QParse_Rules_LogTrace(comma()),
          QParse_Rules_LogTrace(statement_end()),
          QParse_Rules_LogTrace(paren_open()),
          QParse_Rules_LogTrace(brace_open()),
          QParse_Rules_LogTrace(paren_close()),
          QParse_Rules_LogTrace(brace_close()),
          QParse_Rules_LogTrace(digit_or_floating_point()),
          QParse_Rules_LogTrace(op()),
          QParse_Rules_LogTrace(literal_character()),
          QParse_Rules_LogTrace(literal_string()),
          new Rules::Sequence({
            new Rules::NotAt(new Rules::EndOfFile()),
            new Rules::Error("unexpected token")
          })
        })
      })
    ),
    new Rules::EndOfFile()
  });
}

void zlang_create_local_c_file(const std::string s) {
  zlang_command_list[zlang_current_command].file_list.emplace_back(zlang_CMD());
  zlang_CMD & file = zlang_command_list[zlang_current_command].file_list.back();
  auto safe = s.substr(1, s.size()-2);
  std::replace(safe.begin(), safe.end(), '.', '_');
  std::replace(safe.begin(), safe.end(), '/', '_');
  std::replace(safe.begin(), safe.end(), '\\', '_');
  file.name = zlang_command_list[zlang_current_command].name + "(" + zlang_command_list[zlang_current_command].type_string + "):" + safe;
  file.full_name = std::string("_gen_") + zlang_command_list[zlang_current_command].name + "__" + zlang_command_list[zlang_current_command].type_string + "__" + safe + ".c";
  std::string cmd = "cp ";
  cmd += s;
  cmd += " ";
  cmd += file.full_name;
  system(cmd.c_str());
  file.is_c_object = true;
  file.is_cxx_object = false;
  file.is_transpile_object = false;
}

void zlang_create_local_cxx_file(const std::string s) {
  zlang_command_list[zlang_current_command].file_list.emplace_back(zlang_CMD());
  zlang_CMD & file = zlang_command_list[zlang_current_command].file_list.back();
  auto safe = s.substr(1, s.size()-2);
  std::replace(safe.begin(), safe.end(), '.', '_');
  std::replace(safe.begin(), safe.end(), '/', '_');
  std::replace(safe.begin(), safe.end(), '\\', '_');
  file.name = zlang_command_list[zlang_current_command].name + "(" + zlang_command_list[zlang_current_command].type_string + "):" + safe;
  file.full_name = std::string("_gen_") + zlang_command_list[zlang_current_command].name + "__" + zlang_command_list[zlang_current_command].type_string + "__" + safe + ".cxx";
  std::string cmd = "cp ";
  cmd += s;
  cmd += " ";
  cmd += file.full_name;
  system(cmd.c_str());
  file.is_c_object = false;
  file.is_cxx_object = true;
  file.is_transpile_object = false;
}

#define NODE_HEADER size_t & i, size_t e, LEXER_NODE * node
#define NODE_HEADER_ARGS i, e, node
#define NEXT_NODE next_node(i, e)
#define NODE_ERROR(s) { node->error(s); node->print(); exit(1); }

LEXER_NODE * next_node(size_t & i, size_t & e) {
  if (++i == e) { CST.nodes[i-1].error("eof"); exit(1); }
  CST.nodes[i].print();
  return &CST.nodes[i];
}


void process_include(NODE_HEADER) {
  node = NEXT_NODE;
  if (node->is("c")) {
    node = NEXT_NODE;
    if (node->is(LEXER_ID_STRING_LITERAL)) {
      zlang_create_local_c_file(node->str());
    } else {
      NODE_ERROR("expected a string literal");
    }
  } else if (node->is("cxx") || node->is("c++")) {
    node = NEXT_NODE;
    if (node->is(LEXER_ID_STRING_LITERAL)) {
      zlang_create_local_cxx_file(node->str());
    } else {
      NODE_ERROR("expected a string literal");
    }
  } else if (node->is("dir")) {
    node = NEXT_NODE;
    if (node->is(LEXER_ID_STRING_LITERAL)) {
      zlang_command_list[zlang_current_command].include_list.emplace_back(node->str());
    } else {
      NODE_ERROR("expected a string literal");
    }
  }
}

std::vector<size_t> vars;
std::map<std::string, size_t> map_pvars;
std::map<std::string, std::pair<size_t, size_t>> map_fvars;

void process_lexer(NODE_HEADER) {
  node = NEXT_NODE;
  std::string content;
  if (node->is(LEXER_ID_C_IDENT)) {
    auto s = node->str();
    zlang_create_transpile_file(s.c_str());
    map_fvars[s] = std::pair<size_t, size_t>(zlang_current_command, zlang_command_list[zlang_current_command].file_list.size()-1);
    zlang_command_list[zlang_current_command].file_list.back().built = true;
  } else {
    NODE_ERROR("invalid name");
  }
  while(true) {
    if (node->is("#")) {
      node = NEXT_NODE;
      if (node->is("endlexer")) {
        return;
      } else {
        NODE_ERROR("#lexer must end with #endlexer");
      }
    } else {
      node = NEXT_NODE;
    }
  }
}

void process_parser(NODE_HEADER) {
  node = NEXT_NODE;
  std::string content;
  if (node->is(LEXER_ID_C_IDENT)) {
    auto s = node->str();
    zlang_create_transpile_file(s.c_str());
    map_fvars[s] = std::pair<size_t, size_t>(zlang_current_command, zlang_command_list[zlang_current_command].file_list.size()-1);
    zlang_command_list[zlang_current_command].file_list.back().built = true;
  } else {
    NODE_ERROR("invalid name");
  }
  while(true) {
    if (node->is("#")) {
      node = NEXT_NODE;
      if (node->is("endparser")) {
        return;
      } else {
        NODE_ERROR("#parser must end with #endparser");
      }
    } else {
      node = NEXT_NODE;
    }
  }
}

void process_call(NODE_HEADER) {
  std::string content;
  node = NEXT_NODE;
  std::string cmd;
  while(true) {
    if (node->is("#")) {
      node = NEXT_NODE;
      if (node->is("endcall")) {
        printf("executing system call:\n %s\n", cmd.c_str());
        system(cmd.c_str());
        return;
      } else {
        NODE_ERROR("#call must end in #endcall");
      }
    } else if (node->is("$")) {
      node = NEXT_NODE;
      auto it = map_pvars.find(node->str());
      if (it != map_pvars.end()) {
        cmd += zlang_command_list[it->second].full_name.c_str();
        cmd += " ";
      } else {
        auto it = map_fvars.find(node->str());
        if (it != map_fvars.end()) {
          cmd += zlang_command_list[it->second.first].file_list[it->second.second].full_name.c_str();
          cmd += " ";
        } else {
          NODE_ERROR("unknown variable");
        }
      }
    } else if (node->is("-")) {
        cmd += node->str();
        node = NEXT_NODE;
        if (node->is("o")) {
          cmd += node->str();
          cmd += " ";
        }
    } else if (node->is(".")) {
        cmd += node->str();
        node = NEXT_NODE;
        if (node->is("c")) {
          cmd += node->str();
          cmd += " ";
        } else if (node->is("/")) {
          cmd += node->str();
        }
    } else {
        cmd += node->str();
        cmd += " ";
    }
    node = NEXT_NODE;
  }
}

void process_exe(NODE_HEADER) {
  node = NEXT_NODE;
  if (node->is(LEXER_ID_C_IDENT)) {
    auto s = node->str();
    zlang_create_exe(s.c_str());
    map_pvars[s] = zlang_current_command;
  } else {
    NODE_ERROR("invalid name");
  }
}

void process_exe_build(NODE_HEADER) {
  node = NEXT_NODE;
  if (!node->is("$")) NODE_ERROR("must specify an exe variable");
  node = NEXT_NODE;
  auto it = map_pvars.find(node->str());
  if (it != map_pvars.end()) {
    zlang_link_command(zlang_command_list[it->second]);
  } else {
    NODE_ERROR("unknown exe variable");
  }
}

void process_nolink(NODE_HEADER) {
  zlang_create_no_link();
}

void process_directive(NODE_HEADER) {
  node = NEXT_NODE;
  if (node->is("include")) {
    process_include(NODE_HEADER_ARGS);
  } else if (node->is("lexer")) {
    process_lexer(NODE_HEADER_ARGS);
  } else if (node->is("parser")) {
    process_parser(NODE_HEADER_ARGS);
  } else if (node->is("call")) {
    process_call(NODE_HEADER_ARGS);
  } else if (node->is("exe")) {
    process_exe(NODE_HEADER_ARGS);
  } else if (node->is("buildexe")) {
    process_exe_build(NODE_HEADER_ARGS);
  } else if (node->is("nolink")) {
    process_nolink(NODE_HEADER_ARGS);
  }
}

struct ClassInfo;

struct VariableInfo {
  LEXER_NODE type;
  LEXER_NODE name;
  std::vector<LEXER_NODE> initial_assignment;
  ClassInfo * parent_class = nullptr;
};

struct FunctionInfo {
  LEXER_NODE type;
  LEXER_NODE name;
  std::vector<LEXER_NODE> parens;
  std::vector<LEXER_NODE> body;
  ClassInfo * parent_class = nullptr;
};

struct ClassInfo {
  LEXER_NODE name;
  std::vector<VariableInfo> variable_list;
  std::vector<FunctionInfo> function_list;
  std::vector<ClassInfo*> class_list;
  FunctionInfo constructor;
  std::vector<LEXER_NODE> destructor_body;
  ClassInfo * parent_class = nullptr;

  void print() { print(""); }
  
  void print(const std::string & idt) {
    const char * indent = idt.c_str();
    printf("%sclass ", indent);
    if (name.str().size() != 0) {
      auto s = name.str();
      printf("%s ", s.c_str());
    }
    printf("[\n");
    printf("%s  variables [\n", indent);
    for (auto v : variable_list) {
      auto t = v.type.str();
      printf("%s      [type] %s\n", indent, t.c_str());
      auto n = v.name.str();
      printf("%s      [name] %s\n", indent, n.c_str());
      if (v.initial_assignment.size() == 0) {
        printf("%s      [declaration]\n", indent);
      } else {
        for (auto b : v.initial_assignment) {
          auto v = b.str();
          printf("%s      [definition] %s\n", indent, v.c_str());
        }
      }
    }
    printf("%s  ]\n", indent);
    printf("%s  constructor [\n", indent);
    {
      auto f = constructor;
      auto t = f.type.str();
      printf("%s      [type] %s\n", indent, t.c_str());
      auto n = f.name.str();
      printf("%s      [name] %s\n", indent, n.c_str());
      if (f.parens.size() == 0) {
        printf("%s      [no arguments]\n", indent);
      } else {
        for (auto b : f.parens) {
          auto v = b.str();
          printf("%s    [arguments] %s\n", indent, v.c_str());
        }
      }
      if (f.body.size() == 0) {
        printf("%s      [no body]\n", indent);
      } else {
        for (auto & b : f.body) {
          auto v = b.str();
          printf("%s    [body] %s\n", indent, v.c_str());
        }
      }
    }
    printf("%s  ]\n", indent);
    printf("%s  destructor [\n", indent);
    if (destructor_body.size() == 0) {
      printf("%s      [no body]\n", indent);
    } else {
      for (auto b : destructor_body) {
        auto v = b.str();
        printf("%s    [body] %s\n", indent, v.c_str());
      }
    }
    printf("%s  ]\n", indent);
    printf("%s  functions [\n", indent);
    for (auto f : function_list) {
      auto t = f.type.str();
      printf("%s      [type] %s\n", indent, t.c_str());
      auto n = f.name.str();
      printf("%s      [name] %s\n", indent, n.c_str());
      if (f.parens.size() == 0) {
        printf("%s      [no arguments]\n", indent);
      } else {
        for (auto b : f.parens) {
          auto v = b.str();
          printf("%s    [arguments] %s\n", indent, v.c_str());
        }
      }
      if (f.body.size() == 0) {
        printf("%s      [no body]\n", indent);
      } else {
        for (auto b : f.body) {
          auto v = b.str();
          printf("%s    [body] %s\n", indent, v.c_str());
        }
      }
    }
    printf("%s  ]\n", indent);
    printf("%s  child scopes [\n", indent);
    if (class_list.size() == 0) {
      printf("%s      [no child scope]\n", indent);
    } else {
      for (auto & b : class_list) b->print(idt + "    ");
    }
    printf("%s  ]\n", indent);
    printf("%s]\n", indent);
  }
};

// keep the syntax simple since we are currently inside a standard C++ source file and have a limited parser

void parse_statement_or_expression(NODE_HEADER, bool in_block_scope, std::vector<LEXER_NODE> * body) {
  if (node->is(LEXER_ID_STATEMENT_SEPERATOR)) {
    node = NEXT_NODE;
    return;
  }
  {
    node = NEXT_NODE;
    return;
  }
  //NODE_ERROR("parse statement or expression");
  if (node->is(LEXER_ID_PAREN_CLOSE) || node->is(LEXER_ID_BRACE_CLOSE)) {
    if (in_block_scope) {
      i--;
      return;
    } else {
      NODE_ERROR("did not expect a paren or brace in a non block expression");
    }
  }
  if (node->is(LEXER_ID_STATEMENT_SEPERATOR)) {
    if (in_block_scope) {
      node = NEXT_NODE;
      return;
    } else {
      return;
    }
  }
  if (node->is(LEXER_ID_C_IDENT)) {
    auto st = node->str();
    if (st == "return") {
      if (!in_block_scope) {
        NODE_ERROR("a statement is not allowed in an expression");
      } else {
        body->emplace_back(*node);
      }
    } else if (st == "while") {
      if (!in_block_scope) {
        NODE_ERROR("a statement is not allowed in an expression");
      } else {
        body->emplace_back(*node);
      }
    } else if (st == "for") {
      if (!in_block_scope) {
        NODE_ERROR("a statement is not allowed in an expression");
      } else {
        body->emplace_back(*node);
      }
    } else {
      if (!in_block_scope) {
        body->emplace_back(*node);
      } else {
        body->emplace_back(*node);
      }
    }
  } else {
    if (!in_block_scope) {
      body->emplace_back(*node);
    } else {
      body->emplace_back(*node);
    }
  }
}

void parse_block(NODE_HEADER, std::vector<LEXER_NODE> * body) {
  node = NEXT_NODE;
  if (!node->is(LEXER_ID_BRACE_OPEN)) NODE_ERROR("expected a '{' while parsing a block level scope");
  body->emplace_back(*node);
  int brace_count = 1;
  while (true) {
    node = NEXT_NODE;
    if (node->is(LEXER_ID_BRACE_OPEN)) {
      body->emplace_back(*node);
      brace_count++;
      parse_statement_or_expression(NODE_HEADER_ARGS, true, body);
    } else if (node->is(LEXER_ID_BRACE_CLOSE)) {
      body->emplace_back(*node);
      brace_count--;
      if (brace_count == 0) return;
      parse_statement_or_expression(NODE_HEADER_ARGS, true, body);
    } else {
      i--;
      parse_statement_or_expression(NODE_HEADER_ARGS, true, body);
    }
  }
}

void parse_parens_block(NODE_HEADER, std::vector<LEXER_NODE> * body) {
  node = NEXT_NODE;
  if (!node->is(LEXER_ID_PAREN_OPEN)) NODE_ERROR("expected a '(' while parsing a parenthesis block level scope");
  body->emplace_back(*node);
  int brace_count = 1;
  while (true) {
    node = NEXT_NODE;
    if (node->is(LEXER_ID_PAREN_OPEN)) {
      body->emplace_back(*node);
      brace_count++;
      parse_statement_or_expression(NODE_HEADER_ARGS, false, body);
    } else if (node->is(LEXER_ID_PAREN_CLOSE)) {
      body->emplace_back(*node);
      brace_count--;
      if (brace_count == 0) return;
      parse_statement_or_expression(NODE_HEADER_ARGS, false, body);
    } else {
      i--;
      parse_statement_or_expression(NODE_HEADER_ARGS, true, body);
    }
  }
}

void parse_variable_or_function(NODE_HEADER, ClassInfo * parent) {
  node = NEXT_NODE;
  if (!node->is(LEXER_ID_C_IDENT)) NODE_ERROR("expected a type while parsing a variable or function level scope");
  auto saved_type = *node;
  node = NEXT_NODE;
  if (!node->is(LEXER_ID_C_IDENT)) NODE_ERROR("expected a name while parsing a variable or function level scope");
  auto saved_name = *node;
  node = NEXT_NODE;
  if (!(node->is(LEXER_ID_PAREN_OPEN) || node->is(":"))) {
    VariableInfo v;
    v.type = saved_type;
    v.name = saved_name;
    v.parent_class = parent;
    parent->variable_list.emplace_back(std::move(v));
    i--;
    parse_statement_or_expression(NODE_HEADER_ARGS, false, &parent->variable_list.back().initial_assignment);
    return;
  }
  
  while (true) {
    if (node->is(LEXER_ID_PAREN_OPEN)) break;
    if (!node->is(LEXER_ID_C_IDENT)) {
      if (node->is(":")) {
        node = NEXT_NODE;
        if (!node->is(":")) {
          NODE_ERROR("expected a namespace '::' but only got a single ':'");
        }
        node = NEXT_NODE;
        if (!node->is(LEXER_ID_C_IDENT)) {
          NODE_ERROR("expected a namespace '::' to be followed by an identifier");
        }
        continue;
      }
      NODE_ERROR("expected a namespace :: or an identifier");
    }
    node = NEXT_NODE;
    continue;
  }
  
  i--;
  
  FunctionInfo f;
  f.type = saved_type;
  f.name = saved_name;
  f.parent_class = parent;
  parent->function_list.emplace_back(std::move(f));
  
  auto ffv = &parent->function_list.back().parens;
  auto ffp = &parent->function_list.back().body;

  parse_parens_block(NODE_HEADER_ARGS, ffv);
  parse_block(NODE_HEADER_ARGS, ffp);
}

void parse_variable_or_member_function(NODE_HEADER, ClassInfo * parent) {
  node = NEXT_NODE;
  if (parent->name.str().size() == 0) {
    
    // an anonymous class cannot have a constructor nor a destructor
    // however it has an implicit default constructor and an implicit default destructor
    //
    if (node->is(LEXER_ID_C_IDENT)) {
      node = NEXT_NODE;
      if (node->is(LEXER_ID_PAREN_OPEN)) NODE_ERROR("an anonymous class cannot have a constructor");
      i--;
      node = &CST.nodes[i];
    }
    if (node->is(LEXER_ID_PAREN_OPEN)) NODE_ERROR("an anonymous class cannot have a constructor");
    if (node->is("~")) NODE_ERROR("an anonymous class cannot have a destructor");
  } else {
    // a named class can have a constructor and a destructor
    // however it has an implicit default constructor and an implicit default destructor
    //
    // zlang_Input();
    // zlang_Input(const zlang_Input & x);
    // zlang_Input(zlang_Input && x);
    // zlang_Input & operator=(const zlang_Input & x);
    // zlang_Input & operator=(zlang_Input && x);
    // ~zlang_Input();
    //
    
    if (node->is(parent->name.str())) {
      // constructor
      //
      parse_parens_block(NODE_HEADER_ARGS, &parent->constructor.parens);
      parse_block(NODE_HEADER_ARGS, &parent->constructor.body);
      return;
    } else if (node->is("~")) {
      node = NEXT_NODE;
      if (!node->is(parent->name.str()) && !node->is(LEXER_ID_PAREN_OPEN)) NODE_ERROR("a destructor must specify the class name 'class foo { ~foo(); }' or be specified as 'class foo { ~(); }'");
      node = NEXT_NODE;
      if (!node->is(LEXER_ID_PAREN_CLOSE)) NODE_ERROR("an destructor must have zero arguments");
      parse_block(NODE_HEADER_ARGS, &parent->destructor_body);
      return;
    }
  }
  
  if (!node->is(LEXER_ID_C_IDENT)) NODE_ERROR("expected a type while parsing a variable or function level scope");
  auto saved_type = *node;
  node = NEXT_NODE;
  if (!node->is(LEXER_ID_C_IDENT)) NODE_ERROR("expected a name while parsing a variable or function level scope");
  auto saved_name = *node;
  node = NEXT_NODE;
  if (!node->is(LEXER_ID_PAREN_OPEN)) {
    VariableInfo v;
    v.type = saved_type;
    v.name = saved_name;
    v.parent_class = parent;
    parent->variable_list.emplace_back(std::move(v));
    i--;
    parse_statement_or_expression(NODE_HEADER_ARGS, false, &parent->variable_list.back().initial_assignment);
    return;
  }
  
  i--;
  
  FunctionInfo f;
  f.type = saved_type;
  f.name = saved_name;
  f.parent_class = parent;
  parent->function_list.emplace_back(std::move(f));
  
  auto & ff = parent->function_list.back();

  parse_parens_block(NODE_HEADER_ARGS, &ff.parens);
  parse_block(NODE_HEADER_ARGS, &ff.body);
}

void parse_class_block(NODE_HEADER, ClassInfo * parent) {
  node = NEXT_NODE;
  if (!node->is(LEXER_ID_BRACE_OPEN)) NODE_ERROR("expected a '{' while parsing a block level scope");
  int brace_count = 1;
  while (true) {
    node = NEXT_NODE;
    if (node->is(LEXER_ID_BRACE_OPEN)) NODE_ERROR("a class cannot contain block scopes 'class foo { { } }' ");
    if (node->is(LEXER_ID_BRACE_CLOSE)) return;
    i--;
    parse_variable_or_member_function(NODE_HEADER_ARGS, parent);
  }
}

void parse_class(NODE_HEADER, ClassInfo * parent) {
  ClassInfo * c = new ClassInfo();
  c->parent_class = parent;
  parent->class_list.emplace_back(c);
  node = NEXT_NODE;
  if (node->is(LEXER_ID_C_IDENT)) {
    c->name = *node;
  } else {
    i--;
  }
  parse_class_block(NODE_HEADER_ARGS, c);
  node = NEXT_NODE;
  if (!node->is(LEXER_ID_STATEMENT_SEPERATOR)) {
    i--;
    node = &CST.nodes[i];
  }
}

void process_node(NODE_HEADER, ClassInfo * parent) {
  node = NEXT_NODE;
  if (node->is("class")) {
    parse_class(NODE_HEADER_ARGS, parent);
  } else {
    i--;
    parse_variable_or_function(NODE_HEADER_ARGS, parent);
    //zlang_output << node.str() << " ";
  }
}

struct TypeChecker {
  std::function<std::string()> lexer;
};

void translate(ClassInfo * root) {
  TypeChecker tc;
}

int main(int argc, char **argv) {
    zlang_c_compiler = argv[1];
    zlang_cxx_compiler = argv[2];
    printf("c compiler: %s\n", zlang_c_compiler);
    printf("c++ compiler: %s\n", zlang_cxx_compiler);
    printf("processing file: %s\n", argv[3]);
    if (zlang_push_input(argv[3])) {
      auto it = QParse::Iterator(zlang_inputs[zlang_current].input);
      it.name = argv[3];
      it.enable_logging = true;
      zlang_create_exe("parser_v1");
      zlang_create_c_file("parser_v1");
      ClassInfo * root = new ClassInfo();
      printf("lexing...\n");
      if (QParse::Rules::Sequence({parse()}).match(it)) {
        printf("lexing complete\n");
        printf("parsing...\n");
        for (size_t i = 0, e = CST.nodes.size(); i < e;) {
          auto* node = &CST.nodes[i];
          if (node->is("#")) {
            process_directive(NODE_HEADER_ARGS);
          } else {
            i--;
            process_node(NODE_HEADER_ARGS, root);
          }
          i++;
        }
      }
      printf("parsing complete\n");
     
      root->print();
      
      translate(root);
      
      delete root;
      zlang_finalize();
    }
}