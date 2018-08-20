cmake_minimum_required(VERSION 3.6)
PROJECT(cpp_algorithms)

# C++ 11
INCLUDE_DIRECTORIES(cpp/include)
SET(CMAKE_CXX_STANDARD 17)

# Disable usage of TR1 (Tuple is not needed in our case)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DGTEST_HAS_TR1_TUPLE=0")

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(cpp)