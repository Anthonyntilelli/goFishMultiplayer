# add_subdirectory(config)

add_executable(goFishServer.out main.cpp)


target_link_libraries(goFishServer.out
    PRIVATE
    nlohmann_json::nlohmann_json
)
