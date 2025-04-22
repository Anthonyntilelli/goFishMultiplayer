# src/deck/CMakeLists.txt
add_library(deck STATIC deck.cpp deck.hpp)

target_include_directories(deck PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
