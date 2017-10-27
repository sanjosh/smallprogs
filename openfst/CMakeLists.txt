
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

ADD_EXECUTABLE(fst1
  fst1.cpp
	)

TARGET_LINK_LIBRARIES(fst1
	fstscript
	fst
	glog
	dl
	)

