add_library(test_core_lib
    unit_test/test_main.cpp
)

add_executable(test_suite
    unit_test/test_utilities.cpp
    unit_test/test_file_system.cpp
    unit_test/test_boris_corrector.cpp
)
add_dependencies(test_suite test_core_lib boris_corrector_lib)
target_link_libraries(test_suite test_core_lib boris_corrector_lib)

add_test(NAME unit_test COMMAND test_suite)
add_test(NAME system_test COMMAND ${CMAKE_COMMAND}
    -DTARGET=$<TARGET_FILE:boris_corrector>
    -P ${CMAKE_CURRENT_SOURCE_DIR}/system_test/run_test.cmake
)