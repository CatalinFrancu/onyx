# Kudos https://github.com/ttroy50/cmake-examples/blob/master/01-basic/B-hello-headers/CMakeLists.txt
cmake_minimum_required(VERSION 4.0)

# Set the project name
project (onyx)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "src/*.cpp")

add_executable(onyx ${SOURCES})

target_include_directories(onyx
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
