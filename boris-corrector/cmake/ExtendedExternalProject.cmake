include(ExternalProject)
set_property(DIRECTORY PROPERTY EP_BASE ${CMAKE_BINARY_DIR}/external)

set(COPY_FILE ${CMAKE_COMMAND} -E copy)
set(COPY_DIR ${CMAKE_COMMAND} -E copy_directory)
set(EXEC_AT ${CMAKE_COMMAND} -E chdir)
set(MAKE_DIR ${CMAKE_COMMAND} -E make_directory)
set(REMOVE_FILE ${CMAKE_COMMAND} -E remove)
set(REMOVE_DIR ${CMAKE_COMMAND} -E remove_directory)
set(RENAME ${CMAKE_COMMAND} -E rename)

macro(ExternalProject_Generate_Paths name)
    get_property(base DIRECTORY PROPERTY EP_BASE)

    set(${name}_TMP_DIR ${base}/tmp/${name})
    set(${name}_STAMP_DIR ${base}/Stamp/${name})
    set(${name}_DOWNLOAD_DIR ${base}/Download/${name})
    set(${name}_SOURCE_DIR ${base}/Source/${name})
    set(${name}_BINARY_DIR ${base}/Build/${name})
    set(${name}_INSTALL_DIR ${base}/Install/${name})

    set(${name}_INCLUDE_DIR ${base}/Install/${name}/include)
    set(${name}_LIBRARY_DIR ${base}/Install/${name}/lib)

    unset(base)
endmacro()
