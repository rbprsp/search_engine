cmake_minimum_required(VERSION 3.5)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

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

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


add_executable(${PROJECT_NAME} 
        src/main.cpp
        src/converter/converter.cpp
        src/utils/utils.cpp
)

set(FTXUI_QUIET ON) #removig ftxui from cmake output

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/deps/googletest")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/deps/FTXUI")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tests")

target_link_libraries(${PROJECT_NAME} 
                        PRIVATE ftxui::screen
                        PRIVATE ftxui::dom
                        PRIVATE ftxui::component
)

