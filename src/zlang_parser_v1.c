#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern const char * zlang_c_compiler;
extern const char * zlang_cxx_compiler;

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

void zlang_write_s(const char * str) {
  zlang_write(str, strlen(str));
}

typedef struct zlang_buffer {
  char * buffer;
  size_t size;
  size_t growth_size;
  size_t write_index;
  size_t read_index;
} zlang_buffer;

void zlang_buffer_destroy(zlang_buffer * buffer);

void zlang_buffer_create(zlang_buffer * buffer, size_t size, size_t growth_size) {
  buffer->buffer = malloc(sizeof(char)*size);
  if (buffer->buffer == NULL) {
    printf("ran out of memory\n");
    exit(1);
  }
  buffer->size = size;
  buffer->growth_size = growth_size == 0 ? 1 : growth_size;
  buffer->write_index = 0;
  buffer->read_index = 0;
}

void zlang_buffer_resize(zlang_buffer * buffer, size_t size) {
  if (size == 0) {
    zlang_buffer_destroy(buffer);
  } else {
    char * tmp = realloc(buffer->buffer, sizeof(char)*size);
    if (tmp == NULL) {
      printf("ran out of memory\n");
      exit(1);
    }
    buffer->buffer = tmp;
    buffer->size = size;
  }
}

bool zlang_buffer_fill(zlang_buffer * buffer) {
  if (buffer->write_index == 0) {
    int c = zlang_get_input_c();
    if (c == -1) {
      // we ran out of data
      return false;
    }
    // we have data
    buffer->buffer[buffer->write_index++] = (char)c;
    for (size_t i = 1; i < buffer->size; i++) {
      c = zlang_get_input_c();
      if (c == -1) {
        // we ran out of data, truncate the buffer from the end
        zlang_buffer_resize(buffer, i);
        break;
      }
      buffer->buffer[buffer->write_index++] = (char)c;
    }
  } else if (buffer->write_index == buffer->size) {
    int c = zlang_get_input_c();
    if (c == -1) {
      // we ran out of data
      return false;
    }
    // we have data
    zlang_buffer_resize(buffer, buffer->size+buffer->growth_size);
    buffer->buffer[buffer->write_index++] = (char)c;
    for (size_t i = 1; i < buffer->growth_size; i++) {
      c = zlang_get_input_c();
      if (c == -1) {
        // we ran out of data, truncate the buffer from the end
        zlang_buffer_resize(buffer, buffer->size-buffer->growth_size+i);
        break;
      }
      buffer->buffer[buffer->write_index++] = (char)c;
    }
  }
  return true;
}

void zlang_buffer_shrink_from_start(zlang_buffer * buffer, size_t amount) {
  if (amount >= buffer->size) {

    // erase buffer
    //
    zlang_buffer_destroy(buffer);
  } else {

    // move data to start
    //
    memmove(buffer->buffer + amount, buffer, amount);

    // resize buffer
    //
    zlang_buffer_resize(buffer, buffer->size-amount);
    
    // shift the index's to keep pointing to the correct data positions
    //
    if (amount >= buffer->write_index) buffer->write_index -= amount;
    if (amount >= buffer->read_index) buffer->read_index -= amount;
  }
}

size_t zlang_buffer_available_chars(zlang_buffer * buffer) {
  return buffer->write_index == 0 ? 0 : buffer->size - buffer->read_index;
}

char * zlang_buffer_peek(zlang_buffer * buffer) {
  return buffer->write_index == 0 ? NULL : (buffer->size - buffer->read_index) == 0 ? NULL : &buffer->buffer[buffer->read_index];
}

void zlang_buffer_advance(zlang_buffer * buffer) {
  if (buffer->write_index != 0&& (buffer->size - buffer->read_index) != 0) buffer->read_index++;
}

void zlang_buffer_advance_n(zlang_buffer * buffer, size_t amount) {
  if (buffer->write_index != 0&& (buffer->size - buffer->read_index) > amount) buffer->read_index += amount;
}

void zlang_buffer_rewind(zlang_buffer * buffer) {
  if (buffer->write_index != 0&& buffer->read_index != 0) buffer->read_index--;
}

void zlang_buffer_rewind_n(zlang_buffer * buffer, size_t amount) {
  if (buffer->write_index != 0 && buffer->read_index >= amount) buffer->read_index -= amount;
}

void zlang_buffer_seek(zlang_buffer * buffer, size_t position) {
  if (position >= buffer->size) buffer->read_index = buffer->size-1;
  else buffer->read_index = position;
}

void zlang_buffer_destroy(zlang_buffer * buffer) {
  if (buffer->buffer != NULL)
    free(buffer->buffer);

  // reset buffer
  //
  buffer->buffer = NULL;
  buffer->read_index = 0;
  buffer->write_index = 0;
  buffer->size = 0;
}

bool refill(zlang_buffer * buffer) {
  if (!zlang_buffer_fill(buffer)) {
    size_t len = zlang_buffer_available_chars(buffer);
    if (len != 0) {
      zlang_write(zlang_buffer_peek(buffer), len);
    }
    return false;
  }
  return true;
}

typedef struct parser_state {
  const char * main_file;
} parser_state;

void parser_create(parser_state * s) {
  zlang_create_exe(s->main_file);
  zlang_create_c_file(s->main_file);
}

void parser_destroy(parser_state * s) {
  zlang_finalize();
}

parser_state * this_parser = NULL;
zlang_buffer * this_buffer = 0;
const char * this_string = NULL;
size_t this_string_len = 0;

void peek_and_refill() {
  if (this_string_len == 0) {
    if (!refill(this_buffer)) {
      this_string = NULL;
      this_string_len = 0;
      return;
    }
    this_string = zlang_buffer_peek(this_buffer);
    this_string_len = zlang_buffer_available_chars(this_buffer);
  }
}

void skip(size_t len) {
  zlang_buffer_advance_n(this_buffer, len);
  if (this_string_len >= len) {
    this_string += len;
    this_string_len -= len;
    peek_and_refill();
  }
}

void unskip(size_t len) {
  zlang_buffer_rewind_n(this_buffer, len);
  if ((this_string - this_buffer->buffer) >= len) {
    this_string -= len;
    this_string_len += len;
    peek_and_refill();
  }
}

void write_and_skip(const char * buf, size_t len) {
  zlang_write(buf, len);
  skip(len);
}

typedef struct match_data {
  zlang_buffer match;
} match_data;

bool matches_ch(const char ch) {
  return this_string_len >= 1 && this_string[0] == ch;
}

bool matches_range(char low, char high) {
  return this_string_len >= 1 && this_string[0] >= low && this_string[0] <= high;
}

bool matches_str(const char * str) {
  size_t len = strlen(str);
  return this_string_len >= len && memcmp(this_string, str, len) == 0;
}

int matches_newline() {
  if (matches_ch('\r')) {
    skip(1);
    if (matches_ch('\n')) {
      skip(1);
      return 2;
    }
    unskip(1);
  } else if (matches_ch('\n')) {
    skip(1);
    return 1;
  }
  return 0;
}

int matches_whitespace() {
  if (matches_ch('\t') || matches_ch(' ') || matches_ch('\v')) {
    skip(1);
    return 1;
  }
  return matches_newline();
}

int matches_identifier() {
  int match_len = 0;
  LOOP:
  if (matches_range('a', 'z') || matches_range('A', 'Z') || matches_ch('_')) {
    match_len++;
    skip(1);
    if (matches_range('0', '9')) {
      match_len++;
      skip(1);
    }
    goto LOOP;
  }
  return match_len;
}

bool parse_statements() {
  peek_and_refill();
  if (this_string_len == 0) return false;
  
  int matches = 0;
  int len = 0;
  
  len = matches_whitespace(); if (len != 0) matches += len;
  len = matches_identifier(); if (len != 0) {
    matches += len;
    len = matches_whitespace(); if (len != 0) matches += len;
    len = matches_identifier(); if (len != 0) {
      len = matches_whitespace(); if (len != 0) matches += len;
      // we must be a decleration or a definition
      if (matches_ch(';')) {
        len = 1;
        // we matched type ident;
        matches++;
        printf("MATCHED C VARIABLE DECLERATION\n");
        unskip(matches);
        write_and_skip(this_string, matches);
        skip(matches);
        return true;
      }
    }
    unskip(matches);
    write_and_skip(this_string, matches);
    skip(matches);
  } else {
    if (matches == 0) {
      write_and_skip(this_string, 1);
    } else {
      unskip(matches);
      write_and_skip(this_string, matches);
      skip(matches);
    }
  }
  return true;
}

void parse(parser_state * s, zlang_buffer * buffer) {
  this_parser = s;
  this_buffer = buffer;
  while (parse_statements()) {}
}

int main(int argc, char **argv) {
    zlang_c_compiler = argv[1];
    zlang_cxx_compiler = argv[2];
    printf("c compiler: %s\n", zlang_c_compiler);
    printf("c++ compiler: %s\n", zlang_cxx_compiler);
    printf("processing file: %s\n", argv[3]);
    if (zlang_push_input(argv[3])) {
      parser_state parser;
      parser.main_file = "zlang_parser_v3";
      parser_create(&parser);
      zlang_buffer buffer;
      zlang_buffer_create(&buffer, 100, 100);
      parse(&parser, &buffer);
      zlang_buffer_destroy(&buffer);
      parser_destroy(&parser);
    }
    return 0;
}
