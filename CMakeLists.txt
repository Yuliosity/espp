cmake_minimum_required(VERSION 3.1)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

project(espp CXX)

option(ESPP_BUILD_TESTS "Build espp unittests." ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(SOURCE_FILES main.cpp)
add_executable(espp ${SOURCE_FILES} include/espp.hpp include/request.hpp)

if(ESPP_BUILD_TESTS)
    add_subdirectory(test)
    include(CTest)
endif()