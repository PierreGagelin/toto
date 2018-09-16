
toto_add_lib(factory_lib STATIC factory_lib.cpp)

toto_add_test(factory_main factory_main.cpp)
target_link_libraries(factory_main -Wl,--whole-archive factory_lib -Wl,--no-whole-archive)
target_link_libraries(factory_main dl)
