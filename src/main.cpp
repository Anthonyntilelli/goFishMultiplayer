#include "config/serverConfig.hpp"
#include "deck/deck.hpp"
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

int main() {
  std::cout << "Current path is " << fs::current_path() << std::endl;
  // ServerConfig c{};
  // auto results = c.loadConfigFromFile("config/server.json");
  // std::cout << results << std::endl;

  // Deck d{};
  // for (int i = 1; i <= 52; i++) {
  //   std::cout << i << "|" << d.draw() << std::endl;
  // }
  return 1;
}