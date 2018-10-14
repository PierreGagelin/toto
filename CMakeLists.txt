

cmake_minimum_required(VERSION 2.8)
project(toto)


# Generate a JSON file with compilation commands (used with Visual Studio Code)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

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

function (toto_add_lib target_name target_type target_sources)
    add_library(${target_name} ${target_type} "${target_sources}")
    target_compile_options(${target_name} PRIVATE ${COMPILE_OPTION})
    target_include_directories(${target_name} PRIVATE ${INCLUDE_DIR})
endfunction (toto_add_lib)

# Build tests
if (${TOTO_CPP})
    add_subdirectory(cpp)
endif()

if (${TOTO_FACTORY})
    add_subdirectory(factory)
endif()

if (${TOTO_JSON})
    add_subdirectory(json)
endif()

if (${TOTO_PROTOBUF})
    add_subdirectory(protobuf)
endif()

if (${TOTO_ZMQ})
    add_subdirectory(zmq)
endif()
