cmake_minimum_required(VERSION 3.3.2)
project(clang_backend CXX)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

set (CMAKE_BUILD_TYPE "Debug")
set (CMAKE_VERBOSE_MAKEFILE On)

set (CXX_STANDARD "c++11")

execute_process(COMMAND llvm-config --cxxflags 
  OUTPUT_VARIABLE LLVM_CONFIG 
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND llvm-config --libs 
  OUTPUT_VARIABLE LLVM_LIBS 
  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND llvm-config --system-libs
  OUTPUT_VARIABLE LLVM_DEP_LIBS
  OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories(/usr/include/llvm)
include_directories(/usr/lib/llvm-3.8/include/clang)

set(CMAKE_CXX_FLAGS ${LLVM_CONFIG})
#set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")

set(CLANG_LIBS clang clangFrontend clangDriver clangSerialization clangParse 
    clangCodeGen  clangSema clangAnalysis clangEdit clangAST clangLex
    clangBasic )

add_executable(json_match json_match.cpp)
target_link_libraries(json_match ${CLANG_LIBS} ${LLVM_LIBS} ${LLVM_DEP_LIBS})

