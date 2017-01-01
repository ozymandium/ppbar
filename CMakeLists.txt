project(ppbar)
cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_executable(example
    examples/example.cpp
)

# install(TARGETS ppbar
#     LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
# )