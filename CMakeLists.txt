cmake_minimum_required(VERSION 3.12..3.14)
project(aoc2024 LANGUAGES CXX)

# For Modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(Catch2)
FetchCatch2("3.6.0")

include_directories(${PROJECT_SOURCE_DIR}/src/)
# Common functionality
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(aoc_lib STATIC
    ${SRC_FILES})
target_compile_features(aoc_lib PRIVATE cxx_std_20)
target_include_directories(aoc_lib PUBLIC ${PROJECT_SOURCE_DIR}/src/)

# Test Cases 
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
add_subdirectory(${PROJECT_SOURCE_DIR}/inputs)