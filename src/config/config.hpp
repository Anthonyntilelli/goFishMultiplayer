#ifndef CONFIG_H
#define CONFIG_H

#include <expected>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

class Config {
private:
  std::string playerDefaultDefaultNamePrefix{"Player"};
  std::string LoggingLogfile{""};
  unsigned short networkPort = 8000;
  unsigned short networkTimeoutSec = 10;
  unsigned short gameMinPlayers = 2;
  unsigned short gameMaxPlayers = 4;
  unsigned short playerDefaultNameLength = 16;
  bool playerDefaultAllowCustomNames = true;
  bool LoggingEnableLogging = false;
  bool DebugEnableDebuging = false;

public:
  Config() = default;
  ~Config();
};

#endif