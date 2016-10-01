project(ppbar)
cmake_minimum_required(VERSION 2.8)

include_directories(include)
add_library(ppbar SHARED
    src/ppbar.cpp
)

add_executable(example
    examples/example.cpp
)
target_link_libraries(example ppbar)