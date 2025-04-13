cmake_minimum_required(VERSION 4.0.0)
project(GoFishMultiplayer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include CPM
include(FetchContent)
FetchContent_Declare(
  CPM
  GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake
  GIT_TAG v0.40.8
)
FetchContent_MakeAvailable(CPM)

# Add dependencies
CPMAddPackage("gh:nlohmann/json@3.11.3")

# Add your source directory
add_subdirectory(src)

# Add main server executable
add_executable(goFishMultiplayer src/main.cpp)


# Link dependencies to the executable
target_link_libraries(goFishMultiplayer PRIVATE nlohmann_json::nlohmann_json serverConfig)

# Run doxygen on build
find_package(Doxygen REQUIRED)

# Path to your Doxyfile (adjust if needed)
set(DOXYFILE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

add_custom_target(doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)