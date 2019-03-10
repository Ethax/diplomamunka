cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)
project("BORIS Corrector" VERSION 0.1.0 LANGUAGES CXX)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Currently only the GNU Compiler Collection (GCC) is supported.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options("-Wall" "-Wextra" "-pedantic" "-fexceptions")
add_compile_options("$<$<CONFIG:Release>:-O3>")
add_compile_options("$<$<CONFIG:Debug>:-O0;-g3;-ggdb;-fno-inline;-fno-omit-frame-pointer>")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME unit_test COMMAND test/test_suite)