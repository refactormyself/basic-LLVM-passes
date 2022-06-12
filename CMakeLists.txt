cmake_minimum_required(VERSION 3.13.4)
project(llvm-new-passes)

# Pass in the local LLVM installation directory (Please build LLVM from source)
set(LT_LLVM_INSTALL_DIR "" CACHE PATH "LLVM installation directory")

# Tell CMake the location of LLVMConfig.cmake so find_package is not lost :(
list(APPEND CMAKE_PREFIX_PATH "${LT_LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM REQUIRED CONFIG)

# Add used include paths especially llvm
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} include)

# Comform with llvm's C++ standard and setup
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

# Targets:
add_library(AllOpsProfile SHARED src/AllOpsProfilePass.cpp)
add_library(ReplaceMultiply SHARED src/ReplaceMultiplyPass.cpp)

