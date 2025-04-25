cmake_minimum_required(VERSION 3.30)
project(CUDAparser CXX CUDA)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_ARCHITECTURES "native")
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -arch=sm_75")

find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp"
        PATHS /home/progamers/vcpkg/installed/x64-linux/include
        NO_DEFAULT_PATH
)

set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic -fPIE)
elseif(MSVC)
    add_compile_options(/W4 /MP /std:c++latest)
endif()

# Source files
set(CPP_SOURCES
        src/main.cpp
)

set(CUDA_SOURCES
        include/rph_interpreter.cuh
        src/rph_interpreter.cu
)

set_source_files_properties(${CUDA_SOURCES} PROPERTIES LANGUAGE CUDA)

add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${CUDA_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
        /opt/cuda/include
)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXPRTK_INCLUDE_DIRS})

# CUDA settings
set_target_properties(${PROJECT_NAME} PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_RESOLVE_DEVICE_SYMBOLS ON
        CUDA_RUNTIME_LIBRARY "Shared"
        CUDA_ARCHITECTURES "native"
)

# Link against the CUDA runtime library
target_link_libraries(${PROJECT_NAME} PRIVATE cudart nvrtc cuda)