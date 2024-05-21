cmake_minimum_required(VERSION 3.5)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_NAME})

### ----------------
### Search Engine
### ----------------

set(CMAKE_CXX_STANDARD 17)

option(FTXUI_QUIET "" ON)
option(FTXUI_BUILD_EXAMPLES "" OFF)

project(${PROJECT_NAME}
        VERSION 1.0.0
        LANGUAGES CXX
)

#external
include_directories("${CMAKE_CURRENT_LIST_DIR}/deps/json/single_include/nlohmann")
include_directories("${CMAKE_CURRENT_LIST_DIR}/deps/spdlog/include")
include_directories("${CMAKE_CURRENT_LIST_DIR}/deps/googletest/include")

#local
include_directories("${CMAKE_CURRENT_LIST_DIR}/src/logger")
include_directories("${CMAKE_CURRENT_LIST_DIR}/src/converter")
include_directories("${CMAKE_CURRENT_LIST_DIR}/src/index")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

message(STATUS "Adding main executable: ${PROJECT_NAME}")
add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/converter/converter.cpp
        src/index/index.cpp
        src/utils/utils.cpp
)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/deps/googletest")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/deps/FTXUI")



target_link_libraries(${PROJECT_NAME} 
                        PRIVATE ftxui::screen
                        PRIVATE ftxui::dom
                        PRIVATE ftxui::component
)

### ----------------
### Testing
### ----------------

enable_testing()

set(TESING_PROJECT_NAME "${PROJECT_NAME}_tests")

message(STATUS "Adding test executable: ${TESING_PROJECT_NAME}")
add_executable(${TESING_PROJECT_NAME}
        tests/TEST_InvertedIndex.cpp
        src/index/index.cpp
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
