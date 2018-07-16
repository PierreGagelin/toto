

cmake_minimum_required(VERSION 2.8)
project(toto)


# Generate a JSON file with compilation commands (used with Visual Studio Code)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)


# Build type: either Debug or Release
set(CMAKE_BUILD_TYPE Release)


# Allow tests to register themselves as tests
include(CTest)


# Compilation options to add
set(COMPILE_OPTION -std=c++11 -Wall -Wextra)

# Include directory
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

function (toto_add_test target_name target_sources)
    add_executable(${target_name} "${target_sources}")
    target_compile_options(${target_name} PRIVATE ${COMPILE_OPTION})
    target_include_directories(${target_name} PRIVATE ${INCLUDE_DIR})
    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction (toto_add_test)


# Build tests
toto_add_test(tu_smart_ptr tu_smart_ptr.cpp)

toto_add_test(tu_except tu_except.cpp)


add_subdirectory(protobuf)
add_subdirectory(zmq)
