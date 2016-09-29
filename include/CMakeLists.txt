cmake_minimum_required(VERSION 3.2)

set(LIBRARY_NAME YAPDBR)

if (UNIX)
	set(CMAKE_CXX_COMPILER /usr/bin/g++)
endif()

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_YAPDBR
    pdbreader.cpp
    yapdbr.cpp
)

set(HEADERS_YAPDBR
    pdbreader.hh
    yapdbr.hh
)

project(${LIBRARY_NAME})

add_library( ${LIBRARY_NAME} STATIC
             ${HEADERS_YAPDBR}
             ${SOURCE_YAPDBR}
           )

target_include_directories(${LIBRARY_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)

target_include_directories(${LIBRARY_NAME} PRIVATE
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME}> )

enable_testing()
add_subdirectory(tests)
