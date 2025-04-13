# Run doxygen on build
find_package(Doxygen REQUIRED)

set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

add_custom_target(doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)