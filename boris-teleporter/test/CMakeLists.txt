include(ExtendedExternalProject)

ExternalProject_Generate_Paths(catch)
ExternalProject_Add(catch
    URL https://github.com/catchorg/Catch2/archive/v2.0.1.zip
    CONFIGURE_COMMAND ${MAKE_DIR} ${catch_HEADER_DIR}
    BUILD_COMMAND ""
    INSTALL_COMMAND ${COPY_DIR} ${catch_SOURCE_DIR}/single_include ${catch_HEADER_DIR}
)
include_directories(${catch_INCLUDE_DIR})

add_executable(test_suite
    test_main.cpp
    test_boris_teleporter.cpp
)
add_dependencies(test_suite catch boris_teleporter_lib)
target_link_libraries(test_suite boris_teleporter_lib)
