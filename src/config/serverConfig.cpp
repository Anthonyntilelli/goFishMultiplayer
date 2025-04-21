#include "serverConfig.hpp"

std::string ServerConfig::loadConfigFromFile(std::string const &jsonFile) {
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
    if (!enableDebugging.is_null() && enableDebugging.is_boolean()) {
      setDebug(enableDebugging);
    } else {
      return "'enable_debugging' must be define as a boolean in debug setting.";
    }
  }

  return ""; // all passes
}

std::string ServerConfig::setNetworking(const int port,
                                        const int timeoutSeconds) {
  if (port < 1025 || port > 65535)
    return "Network port is not in range: must be between 1025 and 65535.";
  if (timeoutSeconds < 5 || timeoutSeconds > 60)
    return "Network timeout_seconds in not in range: must be between 5 and 60";

  networkPort = static_cast<unsigned short>(port);
  networkTimeoutSec = static_cast<unsigned short>(timeoutSeconds);
  return "";
}

std::string ServerConfig::setGame(const int minPlayer, const int maxPlayer) {
  if (minPlayer > maxPlayer)
    return "Game min_player is greater then max_player.";
  if (minPlayer < 2 || minPlayer > 6)
    return "Game min_player not in range: must be between 2 and 6";
  if (maxPlayer < 2 || maxPlayer > 6)
    return "Game max_player not in range: must be between 2 and 6";
  gameMinPlayers = static_cast<unsigned short>(minPlayer);
  gameMaxPlayers = static_cast<unsigned short>(maxPlayer);
  return "";
}

std::string
ServerConfig::setPlayerDefaults(const int maxNameLength,
                                const bool allowCustomNames,
                                const std::string &defaultNamePrefix) {
  if (maxNameLength < 5 || maxNameLength > 25)
    return "player_defaults max_name_length not in "
           "range: must be between 5 "
           "and 25";

  if (defaultNamePrefix.empty())
    return "player_defaults default_name_prefix cannot be empty.";
  if (defaultNamePrefix.size() > maxNameLength)
    return "player_defaults default_name_prefix is too big.";

  playerDefaultMaxNameLength = static_cast<unsigned short>(maxNameLength);
  playerDefaultAllowCustomNames = allowCustomNames;
  playerDefaultDefaultNamePrefix = defaultNamePrefix;
  return "";
}

std::string ServerConfig::setLogging(const bool enableLogging,
                                     const std::string &logFile) {
  if (enableLogging) {
    std::ofstream file{logFile, std::ios::app};
    if (!file.is_open()) {
      return std::string{"Failed to open file:" + logFile};
    }
  }
  loggingLogfile = logFile;
  loggingEnableLogging = enableLogging;
  return "";
}

void ServerConfig::setDebug(const bool enableDebug) {
  debugEnableDebuging = enableDebug;
}

std::string ServerConfig::getPlayerDefaultDefaultNamePrefix() const {
  return playerDefaultDefaultNamePrefix;
}

std::string ServerConfig::getLoggingLogfile() const { return loggingLogfile; }

unsigned short ServerConfig::getNetworkPort() const { return networkPort; }

unsigned short ServerConfig::getNetworkTimeoutSec() const {
  return networkTimeoutSec;
}

unsigned short ServerConfig::getGameMinPlayers() const {
  return gameMinPlayers;
}

unsigned short ServerConfig::getGameMaxPlayers() const {
  return gameMaxPlayers;
}

unsigned short ServerConfig::getPlayerDefaultMaxNameLength() const {
  return playerDefaultMaxNameLength;
}

bool ServerConfig::getPlayerDefaultAllowCustomNames() const {
  return playerDefaultAllowCustomNames;
}

bool ServerConfig::getLoggingEnableLogging() const {
  return loggingEnableLogging;
}

bool ServerConfig::getDebugEnableDebuging() const {
  return debugEnableDebuging;
};
