# src/player/CMakeLists.txt
add_library(player STATIC player.cpp player.hpp)

target_include_directories(serverConfig PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
