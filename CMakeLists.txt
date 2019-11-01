cmake_minimum_required(VERSION 3.2)
set(LIBRARY_NAME "YAPDBR")
project(${LIBRARY_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SOURCE_YAPDBR
    pdbreader.cpp
    pdbwriter.cpp
    yapdbr.cpp
)

add_library(${LIBRARY_NAME} SHARED
            ${SOURCE_YAPDBR})


enable_testing()
set(TEST_YAPDBR_NAME
	"yapdbr_test")

set(TEST_YAPDBR_SOURCE
	testyapdbr.cpp)

add_executable(${TEST_YAPDBR_NAME} ${TEST_YAPDBR_SOURCE})
target_link_libraries(${TEST_YAPDBR_NAME} PRIVATE ${LIBRARY_NAME})
add_test(${TEST_YAPDBR_NAME} ${TEST_YAPDBR_NAME})
