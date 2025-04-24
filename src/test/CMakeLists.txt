find_package(Catch2 3 REQUIRED)

add_executable(tests
    serverConfig-test.cpp
    deck-test.cpp
    card-test.cpp
    player-test.cpp
)

target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        serverConfig
        deck
        card
        player
)

include(Catch)
catch_discover_tests(tests  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
