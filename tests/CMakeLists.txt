cmake_minimum_required(VERSION 3.20)

set(TESING_PROJECT_NAME tests)

set(SOURCE_FILES 
    "${SOURCE_DIR}/inverted/inverted.cpp"
    "${SOURCE_DIR}/relative/relative.cpp"
)

#external
include_directories("../deps/googletest/include")

#local
include_directories("${SOURCE_DIR}/inverted")
include_directories("${SOURCE_DIR}/relative")


add_executable(${TESING_PROJECT_NAME}
    TEST_InvertedIndex.cpp
    ${SOURCE_FILES}
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




