cmake_minimum_required(VERSION 4.0.0)
project(GoFishMultiplayer VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(genDocs "Automatically run doxygen" ON)
option(staticCheck "Run static check via cppcheck" ON)

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
CPMAddPackage("gh:catchorg/Catch2@3.8.1")

# Add your source directory
add_subdirectory(src)

# Add main server executable
add_executable(goFishMultiplayer src/main.cpp)

# Link dependencies to the executable
target_link_libraries(goFishMultiplayer PRIVATE nlohmann_json::nlohmann_json serverConfig deck card player)

# Add Cmake Modules
list(PREPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
if(genDocs)
  include(docs)
endif()
if(staticCheck)
  include(cppcheck)
endif()

# Adding testing directory
include(CTest)
enable_testing()
add_subdirectory(src/test)