cmake_minimum_required(VERSION 3.10)
project(libsystem_core_test VERSION 0.1.0)

enable_testing()

add_executable(${PROJECT_NAME}
    src/test.cpp
    core/test_format_util.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${GOOGLETEST_SOURCE_DIR}/googletest/include
        ${CMAKE_SOURCE_DIR}/src/core
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        GTest::gtest_main
        GTest::gmock
        libsystem_core
        project_options
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
