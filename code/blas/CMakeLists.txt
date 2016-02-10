project(blastest)
cmake_minimum_required(VERSION 2.6)

enable_language(C)

option(ENABLE_MKL "Compile with Intel MKL?" OFF)

add_executable(main main.c)

if(ENABLE_MKL)
  find_package(BLAS REQUIRED)
  add_definitions(-DHAS_MKL)
  target_link_libraries(main ${BLAS_LIBRARIES})
  list(APPEND CMAKE_C_FLAGS ${BLAS_LINKER_FLAGS})
else()
  find_package(CBLAS REQUIRED)
  target_link_libraries(${CBLAS_LIBRARIES})
endif()
