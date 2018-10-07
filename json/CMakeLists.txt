#
# Use jsmn library
#

include(ExternalProject)

# Configure jsmn as an external project
ExternalProject_Add(project_jsmn
    GIT_REPOSITORY      https://github.com/zserge/jsmn.git
    SOURCE_DIR          ${CMAKE_CURRENT_BINARY_DIR}/jsmn
    BINARY_DIR          ${CMAKE_CURRENT_BINARY_DIR}/jsmn
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       make
    INSTALL_COMMAND     ""
    TEST_COMMAND        make test
)

# Build jsmn library
ExternalProject_Get_Property(project_jsmn BINARY_DIR)
message(STATUS "JSMN binary dir ${BINARY_DIR}")
add_library(jsmn STATIC IMPORTED)
set_property(TARGET jsmn PROPERTY IMPORTED_LOCATION ${BINARY_DIR}/libjsmn.a)
add_dependencies(jsmn project_jsmn)

# Build a test unit using jsmn
ExternalProject_Get_Property(project_jsmn SOURCE_DIR)
toto_add_test(tu_jsmn tu_jsmn.cpp)
target_include_directories(tu_jsmn PRIVATE ${SOURCE_DIR})
target_link_libraries(tu_jsmn jsmn)
