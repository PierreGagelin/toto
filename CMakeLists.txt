

cmake_minimum_required(VERSION 3.0)
project(c3q0)


# Generate a JSON file with compilation commands (used with Visual Studio Code)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)


# Build type: either Debug or Release
set(CMAKE_BUILD_TYPE Release)


# Configure gtest as an external project
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build                 . WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

# Add gtest directly to our build. This defines the gtest and gtest_main targets
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src EXCLUDE_FROM_ALL)

# Allow tests to register themselves as tests
enable_testing()


# Compilation options to add
set(COMPILE_OPTION -std=c++11 -Wall -Wextra)


# Build tests
add_executable(tu_smart_ptr tu_smart_ptr.cpp)
target_compile_options(tu_smart_ptr PRIVATE ${COMPILE_OPTION})
add_test(NAME tu_smart_ptr COMMAND tu_smart_ptr)
target_link_libraries(tu_smart_ptr gtest)
target_link_libraries(tu_smart_ptr gtest_main)

