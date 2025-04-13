#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

/// @brief Holds config for server.

/// Config can be loaded from a Json File.
/// It has a default configuration if a file is not provided to read from.
class ServerConfig {
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

  /// @brief Sets and validates the networking setting.
  /// @param port port server listens on.
  /// @param timeoutSeconds tcp timeout seconds.
  /// @return returns "" if config is loaded without issue or a string of error
  /// if there is an issue.
  std::string setNetworking(const int port, const int timeoutSeconds);

  /// @brief Sets and validates the game setting.
  /// @param minPlayer minimum number of players.
  /// @param maxPlayer max number of players.
  /// @return returns "" if config is loaded without issue or a string of error
  /// if there is an issue.
  std::string setGame(const int minPlayer, const int maxPlayer);

  /// @brief Sets and validates player defaults.
  /// @param maxNameLength max length of a players name.
  /// @param allowCustomNames sets if custom names are allowed.
  /// @param defaultNamePrefix Default naming prefix is custom name is not
  /// provided.
  /// @return returns "" if config is loaded without issue or a string of error
  /// if there is an issue.
  std::string setPlayerDefaults(const int maxNameLength,
                                const bool allowCustomNames,
                                const std::string &defaultNamePrefix);
  /// @brief Sets and validates logging settings.
  /// @param enableLogging sets if logging should take place.
  /// @param logFile file path for logging file.
  /// @return returns "" if config is loaded without issue or a string of error
  /// if there is an issue.
  std::string setLogging(const bool enableLogging, const std::string &logFile);

  /// @brief Sets debug setting
  /// @param enableDebug set if debug should be enabled
  void setDebug(const bool enableDebug);

  std::string getPlayerDefaultDefaultNamePrefix() const;
  std::string getLoggingLogfile() const;
  unsigned short getNetworkPort() const;
  unsigned short getNetworkTimeoutSec() const;
  unsigned short getGameMinPlayers() const;
  unsigned short getGameMaxPlayers() const;
  unsigned short getPlayerDefaultMaxNameLength() const;
  bool getPlayerDefaultAllowCustomNames() const;
  bool getLoggingEnableLogging() const;
  bool getDebugEnableDebuging() const;
};

#endif