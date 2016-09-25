cmake_minimum_required(VERSION 3.2)

link_directories("$<CMAKE_CURRENT_SOURCE_DIR>/../include/")
add_executable(test_yapdbr testyapdbr.cpp)                
target_link_libraries(test_yapdbr YAPDBR)                 
add_test(test_yapdbr ${CMAKE_CURRENT_BINARY_DIR}/test_yapdbr)
