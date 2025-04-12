#include "config/config.hpp"

int main() {
  Config c{};
  c.loadsConfigFromFile("config/server.json");
  return 1;
}