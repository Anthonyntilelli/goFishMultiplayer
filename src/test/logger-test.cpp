//  Tests for logger/logger.hpp"
#include "../logger/logger.hpp"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("Logger correctly initalized.") {
  // Must be first.
  SECTION("Logger throws on incorrect creation") {
    REQUIRE_THROWS_AS(Logger::getInstance("/etc/shadow"), std::runtime_error);
    REQUIRE_THROWS_AS(Logger::getInstance(""), std::runtime_error);
  }
  SECTION("Correct logger is created") {
    REQUIRE_NOTHROW(Logger::getInstance("log/goFish.log"));
    auto &log = Logger::getInstance("log/goFish.log");
    REQUIRE(log.getLogPath() == "log/goFish.log");

    // Logger is a singleton
    REQUIRE_THROWS_AS(Logger::getInstance("log/DeleteMe.log"),
                      std::runtime_error);
    auto &log2 = Logger::getInstance();
    REQUIRE(log2.getLogPath() == "log/goFish.log");
    REQUIRE(&log == &log2);
  }
}
TEST_CASE("Logger will right to the file.") {
  const std::string path = "log/goFish.log";
  auto &log = Logger::getInstance("log/goFish.log");
  auto preSize = fs::file_size(path);
  log.log("debug message");
  auto postSize = fs::file_size(path);
  REQUIRE(postSize > preSize);
}