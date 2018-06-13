

cmake_minimum_required(VERSION 3.0)
project(toto)


# Generate a JSON file with compilation commands (used with Visual Studio Code)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)


# Build type: either Debug or Release
set(CMAKE_BUILD_TYPE Release)


# Allow tests to register themselves as tests
enable_testing()


# Compilation options to add
set(COMPILE_OPTION -std=c++11 -Wall -Wextra)


# Build tests
add_executable(tu_smart_ptr tu_smart_ptr.cpp)
target_compile_options(tu_smart_ptr PRIVATE ${COMPILE_OPTION})
add_test(NAME tu_smart_ptr COMMAND tu_smart_ptr)

