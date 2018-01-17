include(ProcessorCount)

ProcessorCount(MAX_JOBS)
if(MAX_JOBS EQUAL 0)
    set(MAX_JOBS 1)
else()
    math(EXPR MAX_JOBS "${MAX_JOBS} + 1")
endif()
