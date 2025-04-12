#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

/// @brief Holds config for server.

/// Config can be loaded from a Json File.
/// It has a default configuration if a file is not provided to read from.
class Config {
private:
  std::string playerDefaultDefaultNamePrefix{"Player"};
  std::string loggingLogfile{""};
  unsigned short networkPort = 8000;
  unsigned short networkTimeoutSec = 10;
  unsigned short gameMinPlayers = 2;
  unsigned short gameMaxPlayers = 4;
  unsigned short playerDefaultMaxNameLength = 16;
  bool playerDefaultAllowCustomNames = true;
  bool loggingEnableLogging = false;
  bool debugEnableDebuging = false;

public:
  /// @brief Reads the json config file and load the configuration into the
  /// config.
  /// @param jsonFile relative or full path the the json config file.
  /// @return returns "" if config is loaded without issue or a string of error
  /// if there is an issue.
  std::string loadsConfigFromFile(std::string const &jsonFile);

  std::string getPlayerDefaultDefaultNamePrefix() {
    return playerDefaultDefaultNamePrefix;
  };

  std::string getLoggingLogfile() { return loggingLogfile; };
  unsigned short getNetworkPort() { return networkPort; };
  unsigned short getNetworkTimeoutSec() { return networkTimeoutSec; }
  unsigned short getGameMinPlayers() { return gameMinPlayers; };
  unsigned short getGameMaxPlayers() { return gameMaxPlayers; };
  unsigned short getPlayerDefaultMaxNameLength() {
    return playerDefaultMaxNameLength;
  };
  bool getPlayerDefaultAllowCustomNames() {
    return playerDefaultAllowCustomNames;
  };
  bool getLoggingEnableLogging() { return loggingEnableLogging; };
  bool getDebugEnableDebuging() { return debugEnableDebuging; };
};

#endif