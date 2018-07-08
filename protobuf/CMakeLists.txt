

# Add the protobuf package
include(FindProtobuf)
find_package(Protobuf REQUIRED)
set(PROTOBUF_USE_STATIC_LIBS off)


# Build protobuf library
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS toto_pb.proto)
set(SOURCES ${PROTO_SRCS} ${PROTO_HDRS})

add_library(toto_pb STATIC ${SOURCES})
target_compile_options(toto_pb PRIVATE ${COMPILE_OPTION})

target_include_directories(toto_pb PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(toto_pb PUBLIC ${PROTOBUF_INCLUDE_DIRS})

target_link_libraries(toto_pb ${PROTOBUF_LITE_LIBRARIES})
#target_link_libraries(toto_pb ${PROTOBUF_LIBRARIES})


# Build protobuf test
toto_add_test(tu_toto_pb tu_toto_pb.cpp)
target_link_libraries(tu_toto_pb toto_pb)
