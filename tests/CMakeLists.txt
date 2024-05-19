cmake_minimum_required(VERSION 3.5)

set(NAME "${PROJECT_NAME}_tests")

project(${NAME}
    LANGUAGES CXX
    VERSION 1.0.0
)

enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(${NAME}
    TEST_converter.cpp
)

target_link_libraries(${NAME} PUBLIC gtest_main)


add_test(
    NAME ConverterTest
    COMMAND ${NAME}
)