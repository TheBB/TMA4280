project(common-test)
cmake_minimum_required(VERSION 2.6)

add_subdirectory(../common common)

add_executable(common-test main.c)

list(APPEND CMAKE_C_FLAGS ${COMMON_C_FLAGS})
include_directories(${COMMON_INCLUDE_PATHS})
add_definitions(${COMMON_DEFINITIONS})

target_link_libraries(common-test ${COMMON_LIBRARIES})
