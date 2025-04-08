#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

const std::string SERVERCONFIG{"./config/server.json"};

using json = nlohmann::json;

int main(){
    json settingRaw {};
    std::ifstream configFile{SERVERCONFIG};
    if (!configFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    try {
        configFile >> settingRaw;  // May throw if file is malformed
    } catch (const json::parse_error& e) {
        std::cerr << "Parse error at byte " << e.byte << ": " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Parsed JSON:\n" << settingRaw.dump(4) << std::endl;
}