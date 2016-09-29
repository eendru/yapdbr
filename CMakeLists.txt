cmake_minimum_required(VERSION 3.2)

if (UNIX)
	set(CMAKE_CXX_COMPILER /usr/bin/g++)
endif()

set(CMAKE_CXX_STANDARD 11)

set(EXAMPLE_NAME
	example)

project(${EXAMPLE_NAME})

set(EXAMPLE_LIBRARIES
	YAPDBR)
set(EXAMPLE_SOURCE_DIR
	examples)
set(EXAMPLE_SOURCE
	${EXAMPLE_SOURCE_DIR}/main.cpp)

add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
add_subdirectory(include)
enable_testing()
target_link_libraries(${EXAMPLE_NAME} ${EXAMPLE_LIBRARIES})
