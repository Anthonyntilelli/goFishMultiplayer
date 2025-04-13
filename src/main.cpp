#include "config/serverConfig.hpp"
#include <iostream>

int main() {
  ServerConfig c{};
  auto results = c.loadsConfigFromFile("config/server.json");
  std::cout << results << std::endl;
  return 1;
}