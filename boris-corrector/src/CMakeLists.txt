add_library(boris_corrector_lib STATIC boris_corrector.cpp)
target_link_libraries(boris_corrector_lib LINK_INTERFACE_LIBRARIES stdc++fs)

add_executable(boris_corrector main.cpp)
add_dependencies(boris_corrector boris_corrector_lib)
target_link_libraries(boris_corrector PRIVATE boris_corrector_lib)

install(TARGETS boris_corrector DESTINATION .)
