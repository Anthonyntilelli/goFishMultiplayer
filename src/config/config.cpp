#include "config.hpp"

std::string Config::loadsConfigFromFile(std::string const &jsonFile) {
  using json = nlohmann::json;
  json settingRaw{};
  std::ifstream configFile{jsonFile};
  if (!configFile.is_open()) {
    return std::string{"Failed to open file:" + jsonFile};
  }

  try {
    configFile >> settingRaw; // will throw if file is malformed
  } catch (const json::parse_error &e) {
    return std::string{"Invalid Json: " + std::string{e.what()}};
  }

  const auto network = settingRaw.find("network");
  if (network != settingRaw.end()) {
    const auto netvalPort = network.value()["port"];
    const auto netValTimeOut = network.value()["timeout_seconds"];
    if (netvalPort.is_null() || netValTimeOut.is_null())
      return "Both 'port' and 'timeout_seconds' must be defined in network "
             "settings.";
    if (!netvalPort.is_number_integer() || !netValTimeOut.is_number_integer())
      return "Both 'port' and 'timeout_seconds' must be integers in network "
             "settings.";

    auto results = setNetworking(netvalPort, netValTimeOut);
    if (!results.empty())
      return results;
  }

  const auto game = settingRaw.find("game");
  if (game != settingRaw.end()) {
    const auto min = game.value()["min_players"];
    const auto max = game.value()["max_players"];
    if (min.is_null() || max.is_null())
      return "Both 'min_players' and 'max_players' must be defined in game "
             "settings.";
    if (!min.is_number_integer() || !max.is_number_integer())
      return "Both 'min_players' and 'max_players' must be integers in game "
             "settings.";
    const auto results = setGame(min, max);
    if (!results.empty())
      return results;
  }

  const auto playerDefaults = settingRaw.find("player_defaults");
  if (playerDefaults != settingRaw.end()) {
    const auto maxNameLength = playerDefaults.value()["max_name_length"];
    const auto allowCustomNames = playerDefaults.value()["allow_custom_names"];
    const auto defaultNamePrefix =
        playerDefaults.value()["default_name_prefix"];
    if (maxNameLength.is_null() || allowCustomNames.is_null() ||
        defaultNamePrefix.is_null())
      return "'max_name_length', 'allow_custom_names' and "
             "'default_name_prefix' must be defined in the player_defaults "
             "settings.";
    if (!maxNameLength.is_number_integer())
      return "max_name_length must be an integer.";
    if (!allowCustomNames.is_boolean())
      return "allow_custom_names must be a boolean.";
    if (!defaultNamePrefix.is_string())
      return "default_name_prefix must be a string.";

    const auto result =
        setPlayerDefaults(maxNameLength, allowCustomNames, defaultNamePrefix);
    if (!result.empty()) {
      return result;
    }
  }

  const auto logging = settingRaw.find("logging");
  if (logging != settingRaw.end()) {
    const auto enableLogging = logging.value()["enable_logging"];
    const auto logFile = logging.value()["log_file"];
    if (logFile.is_null() || enableLogging.is_null()) {
      return "'enable_logging' and 'log_file' must be defined in logging "
             "setting.";
    }
    if (!logFile.is_string())
      return "'log_file' must be string.";
    if (!enableLogging.is_boolean())
      return "'enable_logging' must be a boolean";

    const auto result = setLogging(enableLogging, logFile);
    if (!result.empty())
      return result;
  }

  const auto debug = settingRaw.find("debug");
  if (debug != settingRaw.end()) {
    const auto enableDebugging = debug.value()["enable_debugging"];
    if (enableDebugging.is_null() && enableDebugging.is_boolean())
      return "'enable_debugging' must be define as a boolean in debug setting.";
    debugEnableDebuging = enableDebugging;
  }

  return ""; // all passes
}

std::string Config::setNetworking(const int port, const int timeoutSeconds) {
  return std::string();
}

std::string Config::setGame(const int minPlayer, const int maxPlayer) {
  return std::string();
}

std::string Config::setPlayerDefaults(const int maxNameLength,
                                      const bool allowCustomNames,
                                      const std::string &defaultNamePrefix) {
  return std::string();
}

std::string Config::setLogging(const bool enableLogging,
                               const std::string &logFile) {
  return std::string();
}
