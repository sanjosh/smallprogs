
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(T CXX)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_COLOR_MAKEFILE)

# these below apply to C and C++ files
add_compile_options(
  -finstrument-functions
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

ADD_LIBRARY(eelib SHARED
	eelib.cpp
	)

ADD_EXECUTABLE(testee
    testee.cpp
	)

TARGET_LINK_LIBRARIES(testee
    eelib
	dl
	)

