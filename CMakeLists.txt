project(cpp_utils)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(GTest MODULE REQUIRED)
message(GTest Found= ${GTEST_FOUND})
message(GTest LIB = ${GTEST_LIBRARIES})
message(GTest Include = ${GTEST_INCLUDE_DIRS})
message(GTest Main Include = ${GTEST_MAIN_LIBRARIES})

include_directories(
    /usr/local/include
    include
    ${GTEST_MAIN_LIBRARIES}
)
file(GLOB_RECURSE src_files src/*.cpp)
message(SRC FILES = ${src_files})
file(GLOB test_files test/test*.cpp) 
add_executable(test_module test/test_main.cc ${test_files} ${src_files})
target_link_libraries(test_module ${GTEST_LIBRARIES})