find_package(Catch2 3 REQUIRED)

add_executable(tests
    serverConfig-test.cpp
)

target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        serverConfig 
)

include(Catch)
enable_testing()

catch_discover_tests(tests  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
