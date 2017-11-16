
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(T CXX)

set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_COLOR_MAKEFILE)

# CMAKE_BUILD_TYPE can be Release/Debug/RelWithDebInfo/MinSizeRel
# For Sanitizer builds, set it to ASan/MSan/TSan.  
# See the CMake directory for sanitizer cmake files
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Debug")
  message(STATUS "To change pass -DCMAKE_BUILD_TYPE on command line")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

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


ADD_EXECUTABLE(build_fst
  build_fst.cpp
	)

TARGET_LINK_LIBRARIES(build_fst
	fstscript
	fst
	glog
	dl
	)

