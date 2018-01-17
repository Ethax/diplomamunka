include(ExtendedExternalProject)
include(MaxSimultaneousJobs)

math(EXPR ADDRESS_MODEL "8 * ${CMAKE_SIZEOF_VOID_P}")

ExternalProject_Generate_Paths(boost)
ExternalProject_Add(boost
    URL https://sourceforge.net/projects/boost/files/boost/1.66.0/boost_1_66_0.zip/download
    CONFIGURE_COMMAND ./bootstrap$<$<BOOL:${UNIX}>:.sh>$<$<BOOL:${WIN32}>:.bat>
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ./b2 -j${MAX_JOBS} variant=release address-model=${ADDRESS_MODEL} link=static
        install --prefix=${boost_INSTALL_DIR} --layout=system
    INSTALL_COMMAND ""
)
include_directories(${boost_INCLUDE_DIR})

set(LIB_PREFIX ${CMAKE_STATIC_LIBRARY_PREFIX}$<$<BOOL:${WIN32}>:lib>)
set(LIB_SUFFIX ${CMAKE_STATIC_LIBRARY_SUFFIX})

add_library(boris_teleporter_lib STATIC
    core_logic/boris_teleporter.cpp
)
add_dependencies(boris_teleporter_lib boost)
target_link_libraries(boris_teleporter_lib LINK_INTERFACE_LIBRARIES
    ${boost_LIBRARY_DIR}/${LIB_PREFIX}boost_filesystem${LIB_SUFFIX}
    ${boost_LIBRARY_DIR}/${LIB_PREFIX}boost_system${LIB_SUFFIX}
    ${boost_LIBRARY_DIR}/${LIB_PREFIX}boost_regex${LIB_SUFFIX}
)

add_executable(boris_teleporter main.cpp)
add_dependencies(boris_teleporter boris_teleporter_lib)
target_link_libraries(boris_teleporter PRIVATE boris_teleporter_lib)

install(TARGETS boris_teleporter DESTINATION .)
