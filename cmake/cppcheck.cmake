file(GLOB_RECURSE CPPCHECK_FILES
    src/*.cpp
    src/*.hpp
)

find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)

if(CPPCHECK_EXECUTABLE)
    add_custom_target(cppcheck ALL
    COMMAND ${CPPCHECK_EXECUTABLE}
            --enable=all
            --check-config
            --inconclusive
            --suppress=missingIncludeSystem
            ${CPPCHECK_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running cppcheck on src/"
    )
else()
    message(FATAL_ERROR "ERROR: Cppcheck not found!")
endif()


