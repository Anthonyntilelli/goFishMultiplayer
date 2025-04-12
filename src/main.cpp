#include "config/config.hpp"
#include <iostream>

int main() {
  Config c{};
  auto results = c.loadsConfigFromFile("config/server.json");
  std::cout << results << std::endl;
  return 1;
}