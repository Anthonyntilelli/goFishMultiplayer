#include "config.hpp"

std::string Config::loadsConfigFromFile(std::string const &jsonFile) {
  using json = nlohmann::json;
  json settingRaw{};
  std::ifstream configFile{jsonFile};
  if (!configFile.is_open()) {
    return std::string{"Failed to open file:" + jsonFile};
  }

  try {
    configFile >> settingRaw; // May throw if file is malformed
  } catch (const json::parse_error &e) {
    return std::string{"Invalid Json: " + std::string{e.what()}};
  }
  settingRaw.at("network");
  // TODO LOAD JSON INTO CONFIG
  return ""; // all passes
}
