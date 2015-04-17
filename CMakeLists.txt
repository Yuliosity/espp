cmake_minimum_required(VERSION 3.1)
project(espp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(ExternalProject)

ExternalProject_Add(rapidjson
  GIT_REPOSITORY https://github.com/miloyip/rapidjson.git
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/rapidjson
  )


set(SOURCE_FILES main.cpp)
add_executable(espp ${SOURCE_FILES} include/espp.hpp include/request.hpp)