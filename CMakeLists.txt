cmake_minimum_required(VERSION 3.13.4)
project(llvm-new-passes)

find_package(LLVM REQUIRED CONFIG)

# Add used include paths especially llvm
include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_BINARY_DIR}/include)

# Conform with llvm's C++ standard and setup
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

# Targets:
add_library(AllOpsProfile SHARED src/AllOpsProfilePass.cpp)
add_library(ReplaceMultiply SHARED src/ReplaceMultiplyPass.cpp)
add_library(ReplaceSubtract SHARED src/ReplaceSubtractPass.cpp)
add_library(RemoveUnreachable SHARED src/RemoveTheUnreachablePass.cpp)
add_library(WrongOpReplace SHARED src/WrongOpReplacePass.cpp)
add_library(FunctionCallsProf SHARED src/FunctionCallsProfilePass.cpp)
add_library(CountMemoryOp SHARED src/MemoryOpCountPass.cpp)
add_library(FunctionInfo SHARED src/FunctionInfoPass.cpp)

add_subdirectory(test)
