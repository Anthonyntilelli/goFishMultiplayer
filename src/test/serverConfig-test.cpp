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
TEST_CASE("Server config sets Game Correctly") {
  ServerConfig c{};
  SECTION("Reject when min > max") {
    REQUIRE(!c.setGame(5, 3).empty());
    REQUIRE(c.getGameMinPlayers() != 5);
    REQUIRE(c.getGameMaxPlayers() != 3);
    REQUIRE(c.setGame(5, 5).empty());
    REQUIRE(c.getGameMinPlayers() == 5);
    REQUIRE(c.getGameMaxPlayers() == 5);
  }
  SECTION("Accepts valid minPlayer") {
    REQUIRE(c.setGame(2, 6).empty());
    REQUIRE(c.getGameMinPlayers() == 2);
    REQUIRE(c.getGameMaxPlayers() == 6);
    REQUIRE(c.setGame(6, 6).empty());
    REQUIRE(c.getGameMinPlayers() == 6);
    REQUIRE(c.getGameMaxPlayers() == 6);
  }
  SECTION("Reject invalid minPlayer") {
    REQUIRE(!c.setGame(-2, 6).empty());
    REQUIRE(c.getGameMinPlayers() != -2);
    REQUIRE(c.getGameMaxPlayers() != 6); // Max will not be set on a failure
    REQUIRE(!c.setGame(7, 99).empty());
    REQUIRE(c.getGameMinPlayers() != 7);
    REQUIRE(c.getGameMaxPlayers() != 99);
  }
  SECTION("Accepts valid maxPlayer") {
    REQUIRE(c.setGame(2, 6).empty());
    REQUIRE(c.getGameMinPlayers() == 2);
    REQUIRE(c.getGameMaxPlayers() == 6);
    REQUIRE(c.setGame(2, 2).empty());
    REQUIRE(c.getGameMinPlayers() == 2);
    REQUIRE(c.getGameMaxPlayers() == 2);
  }
  SECTION("Reject invalid maxPlayer") {
    REQUIRE(!c.setGame(2, 99).empty());
    REQUIRE(c.getGameMinPlayers() == 2);
    REQUIRE(c.getGameMaxPlayers() != 99);
  }
}
TEST_CASE("Server config sets PlayerDefaults Correctly") {
  ServerConfig c{};
  SECTION("Accepts valid maxNameLength") {
    REQUIRE(c.setPlayerDefaults(5, true, "Views").empty());
    REQUIRE(c.getPlayerDefaultMaxNameLength() == 5);
    REQUIRE(c.getPlayerDefaultAllowCustomNames() == true);
    REQUIRE(c.getPlayerDefaultDefaultNamePrefix() == std::string("Views"));
    REQUIRE(c.setPlayerDefaults(25, false, "Player").empty());
    REQUIRE(c.getPlayerDefaultMaxNameLength() == 25);
    REQUIRE(c.getPlayerDefaultAllowCustomNames() == false);
    REQUIRE(c.getPlayerDefaultDefaultNamePrefix() == std::string("Player"));
  }
  SECTION("Rejects invalid maxNameLength") {
    REQUIRE(!c.setPlayerDefaults(-5, true, "Views").empty());
    REQUIRE(c.getPlayerDefaultMaxNameLength() != -5);
    REQUIRE(!c.setPlayerDefaults(999, false, "Player").empty());
    REQUIRE(c.getPlayerDefaultMaxNameLength() != 999);
  }
  SECTION("Sets allowCustomNames correctly") {
    REQUIRE(c.setPlayerDefaults(5, true, "Views").empty());
    REQUIRE(c.getPlayerDefaultAllowCustomNames() == true);
    REQUIRE(c.setPlayerDefaults(25, false, "Player").empty());
    REQUIRE(c.getPlayerDefaultAllowCustomNames() == false);
  }
  SECTION("Accepts valid defaultNamePrefix") {
    REQUIRE(c.setPlayerDefaults(5, true, "Views").empty());
    REQUIRE(c.getPlayerDefaultMaxNameLength() == 5);
    REQUIRE(c.getPlayerDefaultAllowCustomNames() == true);
    REQUIRE(c.getPlayerDefaultDefaultNamePrefix() == std::string("Views"));
    REQUIRE(
        c.setPlayerDefaults(25, false, "pancreaticoduodenectomies").empty());
    REQUIRE(c.getPlayerDefaultMaxNameLength() == 25);
    REQUIRE(c.getPlayerDefaultAllowCustomNames() == false);
    REQUIRE(c.getPlayerDefaultDefaultNamePrefix() ==
            std::string("pancreaticoduodenectomies"));
  }
  SECTION("Reject invalid defaultNamePrefix") {
    REQUIRE(!c.setPlayerDefaults(5, true, "WayTooLong").empty());
    REQUIRE(c.getPlayerDefaultDefaultNamePrefix() != std::string("WayTooLong"));
    REQUIRE(!c.setPlayerDefaults(25, false, "").empty());
    REQUIRE(c.getPlayerDefaultDefaultNamePrefix() != std::string(""));
  }
}
TEST_CASE("Server config sets Logging Correctly") {
  ServerConfig c{};
  SECTION("Sets enableLogging correctly") {
    REQUIRE(c.setLogging(false, "").empty());
    REQUIRE(c.getLoggingEnableLogging() == false);
    REQUIRE(c.getLoggingLogfile() == "");
    REQUIRE(c.setLogging(true, "/tmp/test.log").empty());
    REQUIRE(c.getLoggingEnableLogging() == true);
    REQUIRE(c.getLoggingLogfile() == "/tmp/test.log");
  }
  SECTION("Accepts valid logFile") {
    REQUIRE(c.setLogging(true, "/tmp/test.log").empty());
    REQUIRE(c.getLoggingEnableLogging() == true);
    REQUIRE(c.getLoggingLogfile() == "/tmp/test.log");
  }
  SECTION("Rejects invalid logFile") {
    REQUIRE(!c.setLogging(true, "/etc/shadow").empty());
    REQUIRE(c.getLoggingLogfile() != "/etc/shadow");
  }
}
TEST_CASE("Server config sets Debug Correctly") {
  ServerConfig c{};
  SECTION("Correctly sets enableDebug") {
    c.setDebug(true);
    REQUIRE(c.getDebugEnableDebuging() == true);
    c.setDebug(false);
    REQUIRE(c.getDebugEnableDebuging() == false);
  }
}
TEST_CASE("Server Config loads file correctly") {
  SECTION("Accepts valid debug") {
    ServerConfig c{};
    REQUIRE(c.loadConfigFromFile("./config/tests/valid/debug.json").empty());
    REQUIRE(c.getDebugEnableDebuging() == true);
  }
  SECTION("Accepts valid game") {
    ServerConfig c{};
    REQUIRE(c.loadConfigFromFile("./config/tests/valid/game.json").empty());
    REQUIRE(c.getGameMinPlayers() == 2);
    REQUIRE(c.getGameMaxPlayers() == 4);
  }
  SECTION("Accepts valid logging") {
    ServerConfig c{};
    REQUIRE(c.loadConfigFromFile("./config/tests/valid/logging.json").empty());
    REQUIRE(c.getLoggingEnableLogging() == true);
    REQUIRE(c.getLoggingLogfile() == "./log/goFish.log");
  }
  SECTION("Accepts valid network") {
    ServerConfig c{};
    REQUIRE(c.loadConfigFromFile("./config/tests/valid/network.json").empty());
    REQUIRE(c.getNetworkPort() == 8000);
    REQUIRE(c.getNetworkTimeoutSec() == 10);
  }
  SECTION("Accepts valid playerDefault") {
    ServerConfig c{};
    REQUIRE(c.loadConfigFromFile("./config/tests/valid/playerDefault.json")
                .empty());
    REQUIRE(c.getPlayerDefaultAllowCustomNames() == true);
    REQUIRE(c.getPlayerDefaultDefaultNamePrefix() == "Player");
    REQUIRE(c.getPlayerDefaultMaxNameLength() == 16);
  }
  SECTION("Rejects invalid files") {
    ServerConfig c{};
    REQUIRE(!c.loadConfigFromFile("./config/tests/invalid/empty").empty());
    REQUIRE(!c.loadConfigFromFile("./config/tests/invalid/invalidJSON.json")
                 .empty());
  }
  SECTION("Rejects invalid debug") {
    ServerConfig c{};
    REQUIRE(!c.loadConfigFromFile("./config/tests/invalid/debug.json").empty());
  }
  SECTION("Rejects invalid game") {
    ServerConfig c{};
    REQUIRE(!c.loadConfigFromFile("./config/tests/invalid/game.json").empty());
  }
  SECTION("Rejects invalid logging") {
    ServerConfig c{};
    REQUIRE(
        !c.loadConfigFromFile("./config/tests/invalid/logging.json").empty());
  }
  SECTION("Rejects invalid network") {
    ServerConfig c{};
    REQUIRE(
        !c.loadConfigFromFile("./config/tests/invalid/network.json").empty());
  }
  SECTION("Rejects invalid playerDefault") {
    ServerConfig c{};
    REQUIRE(!c.loadConfigFromFile("./config/tests/invalid/playerDefault.json")
                 .empty());
  }
}