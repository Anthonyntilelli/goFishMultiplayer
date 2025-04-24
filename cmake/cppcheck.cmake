find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)

if(CPPCHECK_EXECUTABLE)
    add_custom_target(cppcheck ALL
        COMMAND ${CPPCHECK_EXECUTABLE}
                --enable=all
                --check-config
                --inconclusive
                --suppress=missingIncludeSystem
                src/
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running cppcheck with strict options on src/"
    )
else()
    message(FATAL_ERROR "cppcheck not found!")
endif()
