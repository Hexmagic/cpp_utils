project(cpp_utils)
cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-fstandalone-debug -Wdeprecated-declarations")
find_package(RapidJSON REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Gtest REQUIRED)
find_package(Boost COMPONENTS system filesystem locale
REQUIRED)
message(${EIGEN3_INCLUDE_DIRS})
include_directories(
    include
    /usr/local/include
    /usr/local/include/pcl-1.12
    ${GTEST_MAIN_LIBRARIES}
   ${EIGEN3_INCLUDE_DIRS}
)

file(GLOB_RECURSE src_files src/*.cpp)
add_executable(test_module test/test_main.cc ${src_files} )
target_link_libraries(test_module ${GTEST_LIBRARIES} ${CMAKE_DL_LIBS} boost_locale boost_filesystem)
add_executable(test test/test.cpp ${src_files})
target_link_libraries(test ${CMAKE_DL_LIBS}   dl pthread  ${RapidJSON_LIBRARIES} ${Eigen3_LIBRARIES} boost_locale boost_filesystem )
