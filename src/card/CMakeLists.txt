# src/player/CMakeLists.txt
add_library(card STATIC card.cpp card.hpp)

target_include_directories(card PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
