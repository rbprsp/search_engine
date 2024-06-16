cmake_minimum_required(VERSION 3.20)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME) #cmake_path(GET ...) was introdused in CMake 3.20
string(REPLACE " " "_" PROJECT_ID ${PROJECT_NAME})

project(${PROJECT_NAME}
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

#external
add_subdirectory("deps/spdlog")
add_subdirectory("deps/googletest")

#local
add_subdirectory(src)
add_subdirectory(tests)
