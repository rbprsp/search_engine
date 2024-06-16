cmake_minimum_required(VERSION 3.20)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME) #cmake_path(GET ...) was introdused in CMake 3.20
string(REPLACE " " "_" PROJECT_ID ${PROJECT_NAME})

### ----------------
### Search Engine
### ----------------

set(CMAKE_CXX_STANDARD 17)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

option(gtest_disable_pthreads on)


project(${PROJECT_NAME}
        VERSION 1.0.0
        LANGUAGES CXX
)

#external
include_directories("deps/json/single_include/nlohmann")
include_directories("deps/spdlog/include")
include_directories("deps/googletest/include")

#local
include_directories("src/logger")
include_directories("src/converter")
include_directories("src/inverted")
include_directories("src/relative")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

message(STATUS "Adding main executable: ${PROJECT_NAME}")
add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/converter/converter.cpp
        src/inverted/inverted.cpp
        src/relative/relative.cpp
)

add_subdirectory("deps/googletest")
add_subdirectory("deps/spdlog")


target_link_libraries(${PROJECT_NAME}
                        spdlog::spdlog
)

### ----------------
### Testing
### ----------------

enable_testing()

set(TESING_PROJECT_NAME "${PROJECT_NAME}_tests")

message(STATUS "Adding test executable: ${TESING_PROJECT_NAME}")
add_executable(${TESING_PROJECT_NAME}
        tests/TEST_InvertedIndex.cpp
        src/inverted/inverted.cpp
        src/relative/relative.cpp
)

target_link_libraries(${TESING_PROJECT_NAME} gtest_main)

add_test(
        NAME TestBasic
        COMMAND ${TESING_PROJECT_NAME}
)

add_test(
        NAME TestBasic2
        COMMAND ${TESING_PROJECT_NAME}
)

add_test(
        NAME TestInvertedIndexMissingWord
        COMMAND ${TESING_PROJECT_NAME}
)

add_test(
        NAME TestSimple
        COMMAND ${TESING_PROJECT_NAME}
)

add_test(
        NAME TestTop5
        COMMAND ${TESING_PROJECT_NAME}
)
