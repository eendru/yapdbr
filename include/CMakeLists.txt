cmake_minimum_required(VERSION 3.2)

PROJECT (yapdbr)

SET(CMAKE_CXX_COMPILER /usr/bin/g++)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCE_YAPDBR
	pdbreader.cpp
    yapdbr.cpp
)

set(HEADER_YAPDBR
    pdbreader.hh
    yapdbr.hh
)

set(PROJECT_BINARY_DIR "$<CMAKE_CURRENT_SOURCE_DIR>/.build/")

add_library(YAPDBR SHARED ${SOURCE_YAPDBR} ${HEADER_YAPDBR})

