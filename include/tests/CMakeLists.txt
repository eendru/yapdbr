cmake_minimum_required(VERSION 3.2)

set(TEST_YAPDBR_NAME
	test_yapdbr)
set (TEST_YAPDBR_SOURCE
	testyapdbr.cpp)

project(${TEST_YAPDBR_NAME})

enable_testing()

add_executable(${TEST_YAPDBR_NAME} ${TEST_YAPDBR_SOURCE})

#${LIBRARY_NAME} is defined from project above
target_link_libraries(${TEST_YAPDBR_NAME} ${LIBRARY_NAME}) 
message(LN = ${LIBRARY_NAME})

add_test(${TEST_YAPDBR_NAME} ${TEST_YAPDBR_NAME})

