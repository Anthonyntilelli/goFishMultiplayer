//  Tests for config/serverConfig
#include "../config/serverConfig.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Server config starts with expected Defaults") {
  ServerConfig c{};

  REQUIRE(c.getPlayerDefaultDefaultNamePrefix() == "Player");
  REQUIRE(c.getLoggingLogfile() == "");
  REQUIRE(c.getNetworkPort() == 8000);
  REQUIRE(c.getNetworkTimeoutSec() == 10);
  REQUIRE(c.getGameMinPlayers() == 2);
  REQUIRE(c.getGameMaxPlayers() == 4);
  REQUIRE(c.getPlayerDefaultMaxNameLength() == 16);
  REQUIRE(c.getPlayerDefaultAllowCustomNames() == true);
  REQUIRE(c.getLoggingEnableLogging() == false);
  REQUIRE(c.getDebugEnableDebuging() == false);
}

TEST_CASE("Server config sets Networking Correctly") {
  ServerConfig c{};
  SECTION("Accepts valid Ports") {
    REQUIRE(c.setNetworking(1025, 10).empty());
    REQUIRE(c.getNetworkPort() == 1025);
    REQUIRE(c.setNetworking(5025, 10).empty());
    REQUIRE(c.getNetworkPort() == 5025);
  }
  SECTION("Rejects invalid valid Ports") {
    REQUIRE(!c.setNetworking(5, 10).empty());
    REQUIRE(c.getNetworkPort() != 5);
    REQUIRE(!c.setNetworking(-99, 10).empty());
    REQUIRE(c.getNetworkPort() != -99);
  }
  SECTION("Accepts valid Network TimeOut") {
    REQUIRE(c.setNetworking(1025, 5).empty());
    REQUIRE(c.getNetworkTimeoutSec() == 5);
    REQUIRE(c.setNetworking(1025, 60).empty());
    REQUIRE(c.getNetworkTimeoutSec() == 60);
  }
  SECTION("Rejects invalid Network TimeOut") {
    REQUIRE(!c.setNetworking(1025, -5).empty());
    REQUIRE(c.getNetworkTimeoutSec() != -5);
    REQUIRE(!c.setNetworking(1025, 9999).empty());
    REQUIRE(c.getNetworkTimeoutSec() != 9999);
  }
}

TEST_CASE("Server config sets Game Correctly") {}
TEST_CASE("Server config sets PlayerDefaults Correctly") {}
TEST_CASE("Server config sets Logging Correctly") {}
TEST_CASE("Server config sets Debug Correctly") {}