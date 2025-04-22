#include "config/serverConfig.hpp"
#include "deck/deck.hpp"
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

int main() {
  std::cout << "Current path is " << fs::current_path() << std::endl;

  return 1;
}