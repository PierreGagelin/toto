

# Add the protobuf package
include(FindProtobuf)
find_package(Protobuf REQUIRED)
set(PROTOBUF_USE_STATIC_LIBS off)


# Build protobuf library
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS test.proto)
set(SOURCES ${PROTO_SRCS} ${PROTO_HDRS})

add_library(pb_person ${SOURCES})
target_compile_options(pb_person PRIVATE ${COMPILE_OPTION})

target_include_directories(pb_person PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(pb_person PUBLIC ${PROTOBUF_INCLUDE_DIRS})

target_link_libraries(pb_person ${PROTOBUF_LITE_LIBRARIES})
#target_link_libraries(pb_person ${PROTOBUF_LIBRARIES})


# Build protobuf test
toto_add_test(tu_pb_person tu_pb_person.cpp)
target_link_libraries(tu_pb_person pb_person)
