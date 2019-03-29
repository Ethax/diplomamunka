get_filename_component(SOURCE_DIR "${CMAKE_SCRIPT_MODE_FILE}" DIRECTORY)
get_filename_component(SOURCE_DIR "${SOURCE_DIR}" REALPATH)
get_filename_component(TARGET_DIR "${TARGET}" DIRECTORY)
get_filename_component(TARGET_DIR "${TARGET_DIR}" REALPATH)

configure_file(${SOURCE_DIR}/drill_1.bm_ ${TARGET_DIR}/images/drill_1.bmp COPYONLY)
configure_file(${SOURCE_DIR}/drill_2.bm_ ${TARGET_DIR}/images/drill_2.bmp COPYONLY)
configure_file(${SOURCE_DIR}/drill_3.bm_ ${TARGET_DIR}/images/drill_3.bmp COPYONLY)

file(TO_NATIVE_PATH "Z:/Former/Project/Directory" PROJECT_ROOT)
configure_file(${SOURCE_DIR}/animation.fa_ ${TARGET_DIR}/logic/animation.fab)
configure_file(${SOURCE_DIR}/counter.SB_ ${TARGET_DIR}/logic/counter.SBL)
configure_file(${SOURCE_DIR}/main.BS_ ${TARGET_DIR}/main.BSY)

file(TO_NATIVE_PATH "${TARGET_DIR}" PROJECT_ROOT)
configure_file(${SOURCE_DIR}/animation.fa_ animation.fa_)
configure_file(${SOURCE_DIR}/counter.SB_ counter.SB_)
configure_file(${SOURCE_DIR}/main.BS_ main.BS_)

execute_process(COMMAND ${TARGET} WORKING_DIRECTORY ${TARGET_DIR} RESULT_VARIABLE ERROR_CODE)
if(ERROR_CODE)
    message(FATAL_ERROR "The command '${TARGET}' exited with code ${ERROR_CODE}.")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -E compare_files animation.fa_ ${TARGET_DIR}/logic/animation.fab
    COMMAND ${CMAKE_COMMAND} -E compare_files counter.SB_ ${TARGET_DIR}/logic/counter.SBL
    COMMAND ${CMAKE_COMMAND} -E compare_files main.BS_ ${TARGET_DIR}/main.BSY
    OUTPUT_VARIABLE ERRORS
    ERROR_VARIABLE ERRORS
)
if(ERRORS)
    message(FATAL_ERROR "${ERRORS}")
endif()

message("Test passed.")