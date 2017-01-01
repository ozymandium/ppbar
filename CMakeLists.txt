project(ppbar)
cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_executable(example
    examples/example.cpp
)

install(DIRECTORY include/ppbar
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)