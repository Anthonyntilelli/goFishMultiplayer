# src/config/CMakeLists.txt
add_library(serverConfig STATIC serverConfig.cpp serverConfig.hpp)

target_include_directories(serverConfig PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(serverConfig PUBLIC nlohmann_json::nlohmann_json)