cmake_minimum_required(VERSION 3.30)
project(CUDAparser CXX CUDA)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_ARCHITECTURES "native")
set(TGUI_DIR "$ENV{HOME}/vcpkg/installed/x64-linux/share/tgui")
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -arch=sm_75")


find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp"
        PATHS /home/progamers/vcpkg/installed/x64-linux/include
        NO_DEFAULT_PATH
)

set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Default to Release build
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic -fPIE)
elseif(MSVC)
    add_compile_options(/W4 /MP /std:c++latest)
endif()

# Source files
set(CPP_SOURCES
        main.cpp
)

set(CUDA_SOURCES
        new_thing.cu
        new_thing.cuh
)

set(SOURCE_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/fonts)


set_source_files_properties(${CUDA_SOURCES} PROPERTIES LANGUAGE CUDA)

# Create executable
add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${CUDA_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
        /opt/cuda/include # Add CUDA includes as SYSTEM includes if needed, or let find_package(CUDA) handle it
)


# CUDA settings (already present and look okay)
set_target_properties(${PROJECT_NAME} PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_RESOLVE_DEVICE_SYMBOLS ON # Usually needed with SEPARABLE_COMPILATION
        CUDA_RUNTIME_LIBRARY "Shared"  # Or Static if preferred
        CUDA_ARCHITECTURES "native"    # Or specific ones like "75" instead of using CMAKE_CUDA_FLAGS
)

if(NOT EXPRTK_INCLUDE_DIRS)
    message(FATAL_ERROR "Could not find exprtk.hpp")
endif()

target_include_directories(CUDAparser PRIVATE ${EXPRTK_INCLUDE_DIRS})