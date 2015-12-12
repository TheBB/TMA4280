project(hello)
cmake_minimum_required(VERSION 2.6)

set(UTILS_SRC hello_utils.c goodbye_utils.c)
add_library(utils ${UTILS_SRC})

add_executable(hello main.c)
target_link_libraries(hello utils)

add_executable(hello_reversed main_reversed.c)
target_link_libraries(hello_reversed utils)
