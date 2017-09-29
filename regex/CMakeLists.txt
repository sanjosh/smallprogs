
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(T C CXX)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_COLOR_MAKEFILE)

set(CXX_STANDARD c++14)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD} -Wnon-virtual-dtor -Woverloaded-virtual -DBOOST_LOG_DYN_LINK")

# these below apply to C and C++ files
add_compile_options(
  -Wall
  -Wextra
  -Wstrict-aliasing
  -Wno-unused-parameter
  -Wno-missing-field-initializers
  -Wchar-subscripts
  -Wpointer-arith
  -Wformat
  -Wformat-security
  -Werror=format-security
  -fstack-protector-all
  -fPIE
  -fpie
  -fPIC
  -fpic
  -pipe
  -fdata-sections
  -ffunction-sections
)

ADD_LIBRARY(re2 STATIC IMPORTED)
SET_TARGET_PROPERTIES(re2 PROPERTIES IMPORTED_LOCATION /usr/local/lib/libre2.a)

ADD_EXECUTABLE(prefix_search prefix_search.cpp)
TARGET_LINK_LIBRARIES(prefix_search re2 pthread)

ADD_EXECUTABLE(regex_search regex_search.cpp)
TARGET_LINK_LIBRARIES(regex_search re2 pthread)

ADD_EXECUTABLE(trigram trigram.cpp)
TARGET_LINK_LIBRARIES(trigram pthread)
