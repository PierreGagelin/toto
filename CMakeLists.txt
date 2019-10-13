

cmake_minimum_required(VERSION 2.8)
project(toto)


# Generate a JSON file with compilation commands (used with Visual Studio Code)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Allow tests to register themselves as tests
include(CTest)

# Compilation options to add
set(COMPILE_OPTION_C -Wall -Wextra)
set(COMPILE_OPTION_CPP ${COMPILE_OPTION_C} -std=c++11)

set(CMAKE_CXX_FLAGS_RELEASE -O2)

# Include directory
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

function (toto_add_exec target_name target_sources)
    add_executable(${target_name} "${target_sources}")
    target_compile_options(${target_name} PRIVATE ${COMPILE_OPTION_CPP})
    target_include_directories(${target_name} PRIVATE ${INCLUDE_DIR})
endfunction (toto_add_exec)

function (toto_add_test target_name target_sources)
    add_executable(${target_name} "${target_sources}")
    target_compile_options(${target_name} PRIVATE ${COMPILE_OPTION_CPP})
    target_include_directories(${target_name} PRIVATE ${INCLUDE_DIR})
    add_test(NAME ${target_name} COMMAND ${target_name})
endfunction (toto_add_test)

# Build tests
if (${TOTO_PROTOBUF})
    add_subdirectory(protobuf)
endif()

if (${TOTO_ZMQ})
    add_subdirectory(zmq)
endif()
