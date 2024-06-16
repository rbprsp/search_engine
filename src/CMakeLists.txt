cmake_minimum_required(VERSION 3.20)

#external
include_directories("../deps/json/single_include/nlohmann")
include_directories("../deps/spdlog/include")

#local
include_directories("converter")
include_directories("relative")
include_directories("inverted")

set(SOURCE_FILES
    "main.cpp"
    "converter/converter.cpp"
    "relative/relative.cpp"
    "inverted/inverted.cpp"
)

add_executable(${PROJECT_NAME}
               ${SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
                        spdlog::spdlog
)