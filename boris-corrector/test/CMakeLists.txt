add_library(test_core_lib test_main.cpp)

add_executable(test_suite
    test_utilities.cpp
    test_file_system.cpp
    test_boris_corrector.cpp
)
add_dependencies(test_suite test_core_lib boris_corrector_lib)
target_link_libraries(test_suite test_core_lib boris_corrector_lib)
