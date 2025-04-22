# src/deck/CMakeLists.txt
add_library(deck STATIC deck.cpp deck.hpp)

target_include_directories(serverConfig PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
