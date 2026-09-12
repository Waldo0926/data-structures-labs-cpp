cmake_minimum_required(VERSION 3.16)
project(data_structures_labs_cpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(data_structures
    src/sequential_stack.cpp
    src/linked_queue.cpp
    src/binary_tree.cpp
    src/threaded_binary_tree.cpp
    src/huffman.cpp
    src/graph.cpp
    src/sorting.cpp
)

target_include_directories(data_structures PUBLIC include)

target_compile_options(data_structures PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

function(add_ds_demo name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE data_structures)
endfunction()

add_ds_demo(stack_demo examples/stack_demo.cpp)
add_ds_demo(queue_demo examples/queue_demo.cpp)
add_ds_demo(tree_demo examples/tree_demo.cpp)
add_ds_demo(threaded_tree_demo examples/threaded_tree_demo.cpp)
add_ds_demo(huffman_demo examples/huffman_demo.cpp)
add_ds_demo(graph_demo examples/graph_demo.cpp)
add_ds_demo(sorting_demo examples/sorting_demo.cpp)

include(CTest)
if(BUILD_TESTING)
    add_executable(data_structures_tests tests/test_main.cpp)
    target_link_libraries(data_structures_tests PRIVATE data_structures)
    add_test(NAME data_structures_tests COMMAND data_structures_tests)
endif()
