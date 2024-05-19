cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME_TESTS "${PROJECT_NAME}_tests")

project(${PROJECT_NAME_TESTS}
    LANGUAGES CXX
    VERSION 1.0.0
)

enable_testing()
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include_directories("${SEARCH_ENGINE_LIST_DIR}/src/index")

add_executable(${PROJECT_NAME_TESTS}
    ${SEARCH_ENGINE_LIST_DIR}/src/index/index.cpp
    TEST_InvertedIndex.cpp
)

target_link_libraries(${PROJECT_NAME_TESTS} PUBLIC gtest_main)

add_test(
    NAME TestBasic
    COMMAND ${PROJECT_NAME_TESTS}
)