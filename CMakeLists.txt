cmake_minimum_required(VERSION 3.30)
project(CUDAparser)

find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp")
target_include_directories(main PRIVATE ${EXPRTK_INCLUDE_DIRS})


set(CMAKE_CXX_STANDARD 20)

add_executable(CUDAparser main.cpp)
