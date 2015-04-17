find_package(GTestSrc)

IF(GTESTSRC_FOUND)

enable_testing()

if (WIN32 AND (NOT CYGWIN) AND (NOT MINGW))
    set(gtest_disable_pthreads ON)
    set(gtest_force_shared_crt ON)
endif()

add_subdirectory(${GTEST_SOURCE_DIR} ${CMAKE_BINARY_DIR}/googletest)
include_directories(${GTEST_INCLUDE_DIR})

set(TEST_LIBRARIES gtest gtest_main)

add_custom_target(tests ALL)

set(UNITTEST_SOURCES
    test_main.cpp
    request_test.cpp
    )

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra")

add_executable(unittest ${UNITTEST_SOURCES})
target_link_libraries(unittest ${TEST_LIBRARIES})

add_test(NAME unittest
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/unittest
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    )

ENDIF(GTESTSRC_FOUND)