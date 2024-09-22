cmake_minimum_required(VERSION 3.5)

project(zlang)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT COMMAND testBuilder_build)
    add_subdirectory(testBuilder)
    testBuilder_set_current_working_directory_to_default_binary_directory()
endif()

#add_subdirectory(QParse)

if (WIN32)
  set(PLATFORM Windows CACHE BOOL "" FORCE)
elseif(APPLE)
  set(PLATFORM Linux CACHE BOOL "" FORCE)
elseif(ANDROID)
  set(PLATFORM Linux CACHE BOOL "" FORCE)
elseif(LINUX)
  set(PLATFORM Linux CACHE BOOL "" FORCE)
else()
  message(FATAL_ERROR "unsupported platform")
endif()

#add_subdirectory(RE-flex)

find_program(BASH_EXE NAMES bash.exe bash)
find_program(GIT_EXE NAMES git.exe git)

if (BASH_EXE AND GIT_EXE)
    execute_process(COMMAND "${BASH_EXE}" "-c" "pwd")
    execute_process(COMMAND "${BASH_EXE}" "-c" "${GIT_EXE} log --pretty=format:'%H' -n 1 > ${CMAKE_CURRENT_SOURCE_DIR}/include/commit.h")
endif()

#add_custom_command(
#    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/gen_lexer.h
#    DEPENDS Reflex
#    COMMAND $<TARGET_FILE:Reflex> --debug ${CMAKE_CURRENT_SOURCE_DIR}/src/spec.yy --header-file=${CMAKE_CURRENT_SOURCE_DIR}/src/gen_lexer.h
#)

#add_custom_command(
#    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/gen_lexer.cpp
#    DEPENDS Reflex ${CMAKE_CURRENT_SOURCE_DIR}/src/gen_lexer.h
#    COMMAND $<TARGET_FILE:Reflex> --debug ${CMAKE_CURRENT_SOURCE_DIR}/src/spec.yy -o ${CMAKE_CURRENT_SOURCE_DIR}/src/gen_lexer.cpp
#)

if (false)
testBuilder_add_include(vcpu2 include)
testBuilder_add_source(vcpu2 src/vcpu2_tests.cpp)
testBuilder_build(vcpu2 EXECUTABLES)
endif()

if (false)
  add_subdirectory(hashlink)
  target_compile_definitions(libhl PRIVATE HL_ANDROID)
endif()

if (true)
if (false)
set(FLEX_VERSION 2.6.4 CACHE BOOL "" FORCE)
set(FLEX_HASH e87aae032bf07c26f85ac0ed3250998c37621d95f8bd748b31f15b33c45ee995 CACHE BOOL "" FORCE)
set(BISON_VERSION 3.8 CACHE BOOL "" FORCE)
# 2.7 https://www.scribd.com/doc/134400858/bison-pdf
#set(BISON_HASH 19bbe7374fd602f7a6654c131c21a15aebdc06cc89493e8ff250cb7f9ed0a831 CACHE BOOL "" FORCE)
# 3.8
set(BISON_HASH d5d184d421aee15603939973a6b0f372f908edfb24c5bc740697497021ad9458 CACHE BOOL "" FORCE)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/flex_download.cmake "file(DOWNLOAD https://github.com/westes/flex/releases/download/v${FLEX_VERSION}/flex-${FLEX_VERSION}.tar.gz ${CMAKE_CURRENT_BINARY_DIR}/flex-${FLEX_VERSION}.tar.gz EXPECTED_HASH SHA256=${FLEX_HASH})\n")

add_custom_target(flex_download ALL
    COMMENT "downloading flex..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P flex_download.cmake
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/flex_extract.cmake "if (NOT EXISTS flex-${FLEX_VERSION}/configure)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_extract.cmake "  file(ARCHIVE_EXTRACT INPUT flex-${FLEX_VERSION}.tar.gz)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_extract.cmake "endif()\n")

add_custom_target(flex_extract ALL
    COMMENT "extracting flex..."
    DEPENDS flex_download
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P flex_extract.cmake
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/flex_configure.cmake "if (NOT EXISTS flex-${FLEX_VERSION}/Makefile)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_configure.cmake "  execute_process(WORKING_DIRECTORY flex-${FLEX_VERSION} COMMAND ./configure --help)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_configure.cmake "  execute_process(WORKING_DIRECTORY flex-${FLEX_VERSION} COMMAND ./configure --prefix=${CMAKE_CURRENT_BINARY_DIR}/flex_install)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_configure.cmake "endif()\n")

add_custom_target(flex_configure ALL
    COMMENT "configuring flex..."
    DEPENDS flex_extract
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P flex_configure.cmake
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/flex_build.cmake "if (NOT EXISTS flex-${FLEX_VERSION}/src/flex)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_build.cmake "  execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flex-${FLEX_VERSION} COMMAND make)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_build.cmake "endif()\n")

add_custom_target(flex_build ALL
    COMMENT "building flex..."
    DEPENDS flex_configure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P flex_build.cmake
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/flex_install.cmake "if (NOT EXISTS flex_install/bin/flex)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_install.cmake "  execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flex-${FLEX_VERSION} COMMAND make install)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/flex_install.cmake "endif()\n")

add_custom_target(flex_install ALL
    COMMENT "installing flex..."
    DEPENDS flex_build
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P flex_install.cmake
)

add_library(flex UNKNOWN IMPORTED)
set_target_properties(flex PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/flex_install/lib/libfl.a)
target_compile_options(flex INTERFACE "-I ${CMAKE_CURRENT_BINARY_DIR}/flex_install/include")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bison_download.cmake "file(DOWNLOAD http://ftp.gnu.org/gnu/bison/bison-${BISON_VERSION}.tar.gz ${CMAKE_CURRENT_BINARY_DIR}/bison-${BISON_VERSION}.tar.gz EXPECTED_HASH SHA256=${BISON_HASH})\n")

add_custom_target(bison_download ALL
    COMMENT "downloading bison..."
    DEPENDS flex_install
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P bison_download.cmake
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bison_extract.cmake "if (NOT EXISTS bison-${BISON_VERSION}/configure)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_extract.cmake "  file(ARCHIVE_EXTRACT INPUT bison-${BISON_VERSION}.tar.gz)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_extract.cmake "endif()\n")

add_custom_target(bison_extract ALL
    COMMENT "extracting bison..."
    DEPENDS flex_download
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P bison_extract.cmake
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bison_configure.cmake "if (NOT EXISTS bison-${BISON_VERSION}/Makefile)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_configure.cmake "  execute_process(WORKING_DIRECTORY bison-${BISON_VERSION} COMMAND ./configure --help)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_configure.cmake "  execute_process(WORKING_DIRECTORY bison-${BISON_VERSION} COMMAND ./configure LEX=${CMAKE_CURRENT_BINARY_DIR}/flex_install/bin/flex --prefix=${CMAKE_CURRENT_BINARY_DIR}/bison_install)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_configure.cmake "endif()\n")

add_custom_target(bison_configure ALL
    COMMENT "configuring bison..."
    DEPENDS bison_extract
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P bison_configure.cmake
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bison_build.cmake "if (NOT EXISTS bison-${BISON_VERSION}/src/bison)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_build.cmake "  execute_process(WORKING_DIRECTORY bison-${BISON_VERSION} COMMAND make)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_build.cmake "endif()\n")

add_custom_target(bison_build ALL
    COMMENT "building bison..."
    DEPENDS bison_configure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P bison_build.cmake
)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/bison_install.cmake "if (NOT EXISTS bison_install/bin/bison)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_install.cmake "  execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bison-${BISON_VERSION} COMMAND make install)\n")
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/bison_install.cmake "endif()\n")

add_custom_target(bison_install ALL
    COMMENT "installing bison..."
    DEPENDS bison_build
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -P bison_install.cmake
)

add_custom_target(flex_help ALL
    DEPENDS flex_install
    DEPENDS bison_install
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flex_install
    COMMAND ./bin/flex --help
)

add_custom_target(bison_help ALL
    DEPENDS bison_install
    DEPENDS flex_help
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bison_install
    COMMAND ./bin/bison --help
)

add_custom_target(c99_flex ALL
    COMMENT "generating 'lex.yy.c'..."
    DEPENDS bison_help
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ./flex_install/bin/flex --header-file=lex.yy.h ${CMAKE_CURRENT_SOURCE_DIR}/c99.l
)
add_custom_target(c99_bison ALL
    COMMENT "generating 'y.tab.c'..."
    DEPENDS c99_flex
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ./bison_install/bin/yacc -d ${CMAKE_CURRENT_SOURCE_DIR}/c99.y
)

add_executable(c99_parser
  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
  ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c
)
target_link_libraries(c99_parser PRIVATE flex)

add_custom_target(c2j_flex ALL
    COMMENT "generating 'lex.yy.c'..."
    DEPENDS bison_help
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ./flex_install/bin/flex -d --header-file=lex.yy.h ${CMAKE_CURRENT_SOURCE_DIR}/c-to-json/flex_tokens.l
)
add_custom_target(c2j_bison ALL
    COMMENT "generating 'y.tab.c'..."
    DEPENDS c99_flex
    BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ./bison_install/bin/yacc -t -d ${CMAKE_CURRENT_SOURCE_DIR}/c-to-json/yacc_syntax.y
)

add_executable(c2j
  ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
  ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c
  c-to-json/alloc_wrap.c
  c-to-json/ast.c
  c-to-json/main.c
  c-to-json/string_tools.c
  c-to-json/typedef_name.c
)
target_include_directories(c2j PRIVATE c-to-json ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(c2j PRIVATE flex)

endif()

set(LIBTCC1_NAME "libtcc.a" CACHE BOOL "" FORCE)

#add_subdirectory(libtcc-cmake)
add_subdirectory(libtcc_zlang)
target_compile_definitions(libtcc PRIVATE CONFIG_TCCDIR="${CMAKE_CURRENT_BINARY_DIR}/libtcc-cmake")
target_compile_definitions(libtcc PUBLIC MEM_DEBUG=1 TAL_INFO=1 ASM_DEBUG=1 PARSE_DEBUG=1 BF_DEBUG=1 SYM_DEBUG=1 INC_DEBUG=1 PP_DEBUG=1 DEBUG_RELOC=1 DEBUG_VERSION=1)
add_executable(tcc libtcc-cmake/src/tcc.c)
target_link_libraries(tcc libtcc)

add_subdirectory(libriscv/emulator)

target_compile_definitions(riscv PRIVATE _GNU_SOURCE=1 _LARGEFILE64_SOURCE=1)

add_subdirectory(mmaptwo-plus)

add_executable(lexer
  src/mmap.cpp
  src/mmap_iterator.cpp
  src/lexer.cpp
)
target_include_directories(lexer PRIVATE include)
target_include_directories(lexer PRIVATE mmaptwo-plus)
target_link_libraries(lexer libtcc mmaptwo_plus riscv)

endif()

if (false)

add_subdirectory(QParse)
#add_subdirectory(typecheck)

add_executable(zlang_parser_v1 src/zlang_parser_v1_core.cpp)
target_include_directories(zlang_parser_v1 PRIVATE QParse)
target_link_libraries(zlang_parser_v1 PRIVATE QParse)
#target_include_directories(zlang_parser_v1 PRIVATE tree-sitter/lib/src)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/GEN_EXE/parser_v1.c
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/parser_v1.z
    DEPENDS zlang_parser_v1
    COMMAND [ -d ${CMAKE_CURRENT_BINARY_DIR}/GEN_EXE ] || mkdir ${CMAKE_CURRENT_BINARY_DIR}/GEN_EXE \; cd ${CMAKE_CURRENT_BINARY_DIR}/GEN_EXE \; $<TARGET_FILE:zlang_parser_v1> "${CMAKE_C_COMPILER}" "${CMAKE_CXX_COMPILER}" "${CMAKE_CURRENT_SOURCE_DIR}/parser_v1.z" \; touch parser_v1.c
)

add_executable(parser_v1_z ${CMAKE_CURRENT_BINARY_DIR}/GEN_EXE/parser_v1.c)

#add_custom_command(
#    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/gen_lexer.cpp
#    DEPENDS Reflex ${CMAKE_CURRENT_SOURCE_DIR}/src/gen_lexer.h
#    COMMAND $<TARGET_FILE:Reflex> --debug ${CMAKE_CURRENT_SOURCE_DIR}/src/spec.yy -o ${CMAKE_CURRENT_SOURCE_DIR}/src/gen_lexer.cpp
#)

endif()

set(ZLANG_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
