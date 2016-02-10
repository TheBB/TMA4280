project(blastest)
cmake_minimum_required(VERSION 2.6)

enable_language(C)

find_package(CBLAS REQUIRED)

add_executable(main main.c)
target_link_libraries(main ${CBLAS_LIBRARIES})
