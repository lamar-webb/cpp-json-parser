cmake_minimum_required(VERSION 4.3)
project(cpp_json_parser)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_json_parser src/main.cpp)

target_compile_options(cpp_json_parser PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Enable testing
include(CTest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()