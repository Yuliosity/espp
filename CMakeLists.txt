cmake_minimum_required(VERSION 3.1)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

project(espp CXX)

option(ESPP_BUILD_TESTS "Build espp unittests." ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

if(ESPP_BUILD_TESTS)
    add_subdirectory(test)
    include(CTest)
endif()