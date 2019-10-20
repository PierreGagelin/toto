
cmake_minimum_required(VERSION 2.8)
project(toto)

# Generate a JSON file with compilation commands (used with Visual Studio Code)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

include(FindProtobuf)
find_package(Protobuf REQUIRED)

# Generate C++ library
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS toto_pb.proto)
set(SOURCES ${PROTO_SRCS} ${PROTO_HDRS})
add_library(toto_pb STATIC ${SOURCES})
target_include_directories(toto_pb PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(toto_pb PUBLIC ${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(toto_pb protobuf)

# Build protobuf test
add_executable(tu_toto_pb tu_toto_pb.cpp)
target_link_libraries(tu_toto_pb toto_pb)

# Generate python
protobuf_generate_python(PROTO_SRCS_PY toto_pb.proto)
add_custom_target(toto_pb_py ALL DEPENDS ${PROTO_SRCS_PY})
configure_file(tu_toto_pb.py tu_toto_pb.py COPYONLY)

#
# Build a protobuf-c example
#

# Generate C library
set(PROTO_FILE toto_pb.proto)
set(PROTO_CMD protoc-c --c_out=${CMAKE_CURRENT_BINARY_DIR} ${PROTO_FILE})
set(PROTO_GEN ${CMAKE_CURRENT_BINARY_DIR}/toto_pb.pb-c.c)
add_custom_command(
    OUTPUT ${PROTO_GEN}
    COMMAND ${PROTO_CMD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${PROTO_FILE}
)

add_library(toto_proto_c STATIC ${PROTO_GEN})

target_link_libraries(toto_proto_c protobuf-c)
target_include_directories(toto_proto_c PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(toto_proto_c PUBLIC /usr/local/include)

# Build test
add_executable(tu_toto_pb_c tu_toto_pb_c.cpp)
target_link_libraries(tu_toto_pb_c toto_proto_c)
