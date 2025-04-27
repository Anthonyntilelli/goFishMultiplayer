# src/table/CMakeLists.txt
add_library(table STATIC table.cpp table.hpp)

target_include_directories(table PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
