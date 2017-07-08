
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(IndexedQueue C CXX)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_COLOR_MAKEFILE)

set(CXX_STANDARD c++14)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CXX_STANDARD} -fsanitize=address -Wnon-virtual-dtor -Woverloaded-virtual -DBOOST_LOG_DYN_LINK")

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

ADD_EXECUTABLE(IndexedQueueMain
    IndexedQueueMain.cpp
	IndexedQueue.cpp
	)

TARGET_LINK_LIBRARIES(IndexedQueueMain
	glog
    gflags)

