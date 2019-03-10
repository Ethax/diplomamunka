add_executable(test_suite
    test_main.cpp
    test_utilities.cpp
    test_file_system.cpp
    test_boris_corrector.cpp
)
add_dependencies(test_suite boris_corrector_lib)
target_link_libraries(test_suite boris_corrector_lib)
