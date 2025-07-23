cmake_minimum_required(VERSION 3.14)
project(biginteger)

# Language and standard settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags (can be customized for different build types)
set(CMAKE_CXX_FLAGS_INIT "-pedantic-errors -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_INIT} -Wall -Wextra -Wno-unused-variable -Wno-self-assign -Wno-deprecated-copy -Wno-reorder -Wno-unused-result")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_INIT} -O3 -DNDEBUG")

# Define the BigInteger library (if BigInteger is in a separate file biginteger.cpp)
add_library(biginteger STATIC src/biginteger.cpp) # Or SHARED

# Define the test executable
add_executable(run_tests test.cpp src/biginteger.cpp) # Create the test executable

# Link BigInteger with the tests (if needed - if test.cpp calls BigInteger functions)
target_link_libraries(run_tests biginteger)
