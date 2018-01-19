cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project("BORIS Teleporter" VERSION 0.1.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompileOptionsCXX14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME unit_test COMMAND test/test_suite)
