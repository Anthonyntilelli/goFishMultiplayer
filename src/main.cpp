#include "config/serverConfig.hpp"
#include <filesystem>
#include <iostream>

int main() {
  std::cout << "Current path is " << std::filesystem::current_path() << '\n';
  ServerConfig c{};
  // auto results = c.loadConfigFromFile("config/server.json");
  auto results = c.loadConfigFromFile("./config/tests/invalid/debug.json");
  std::cout << results << std::endl;
  return 1;
}