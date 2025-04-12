# src/config/CMakeLists.txt
add_library(config STATIC
    config.cpp
    config.hpp
)

target_include_directories(config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(config PUBLIC nlohmann_json::nlohmann_json)