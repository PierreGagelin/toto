

#
# Build a protobuf example
#
include(FindProtobuf)
find_package(Protobuf REQUIRED)

# Generate C++ library
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS toto_pb.proto)
set(SOURCES ${PROTO_SRCS} ${PROTO_HDRS})
add_library(toto_pb STATIC ${SOURCES})
target_compile_options(toto_pb PRIVATE ${COMPILE_OPTION_CPP})
target_include_directories(toto_pb PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(toto_pb PUBLIC ${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(toto_pb protobuf)

# Build protobuf test
toto_add_test(tu_toto_pb tu_toto_pb.cpp)
target_link_libraries(tu_toto_pb toto_pb)

# Generate python
protobuf_generate_python(PROTO_SRCS_PY toto_pb.proto)
add_custom_target(toto_pb_py ALL DEPENDS ${PROTO_SRCS_PY})
configure_file(tu_toto_pb.py tu_toto_pb.py COPYONLY)
add_test(NAME tu_toto_pb_py COMMAND python3 tu_toto_pb.py)

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
target_compile_options(toto_proto_c PRIVATE ${COMPILE_OPTION_C})
target_include_directories(toto_proto_c PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(toto_proto_c PUBLIC /usr/local/include)

# Build test
toto_add_test(tu_toto_pb_c tu_toto_pb_c.cpp)
target_link_libraries(tu_toto_pb_c toto_proto_c)
