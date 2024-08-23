cmake_minimum_required(VERSION 3.5)

project(zlang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT COMMAND testBuilder_build)
    add_subdirectory(testBuilder)
    testBuilder_set_current_working_directory_to_default_binary_directory()
endif()

#add_subdirectory(QParse)

if (WIN32)
  set(PLATFORM Windows)
elseif(APPLE)
  set(PLATFORM Linux)
elseif(ANDROID)
  set(PLATFORM Linux)
elseif(LINUX)
  set(PLATFORM Linux)
else()
  message(FATAL_ERROR "unsupported platform")
endif()

add_subdirectory(mmaptwo-plus)
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

if (true)
testBuilder_add_include(vcpu2 include)
testBuilder_add_source(vcpu2 src/vcpu2_tests.cpp)
testBuilder_build(vcpu2 EXECUTABLES)
endif()

if (true)
testBuilder_add_include(zlang include)
testBuilder_add_include(zlang mmaptwo-plus)
testBuilder_add_include(zlang Composable-List/include)

testBuilder_add_source(zlang src/main.cpp)
testBuilder_add_source(zlang src/ifstream_iterator.cpp)
testBuilder_add_source(zlang src/mmap.cpp)
testBuilder_add_source(zlang src/mmap_iterator.cpp)
testBuilder_add_source(zlang src/token.cpp)

testBuilder_add_library(zlang mmaptwo_plus)
testBuilder_build(zlang EXECUTABLES)
endif()

set(ZLANG_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
