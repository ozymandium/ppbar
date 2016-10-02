project(ppbar)
cmake_minimum_required(VERSION 2.8)

include_directories(include)

add_library(ppbar SHARED
    src/progress_bar.cpp
    src/iterators.cpp
    src/widgets.cpp
)

add_executable(example
    examples/example.cpp
)
target_link_libraries(example ppbar)

install(TARGETS ppbar
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)