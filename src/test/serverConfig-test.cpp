//  Tests for config/serverConfig
#include "../config/serverConfig.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Server config starts with expected Defaults") {
  ServerConfig c{};
  /*
std::string getLoggingLogfile() const;
unsigned short getNetworkPort() const;
unsigned short getNetworkTimeoutSec() const;
unsigned short getGameMinPlayers() const;
unsigned short getGameMaxPlayers() const;
unsigned short getPlayerDefaultMaxNameLength() const;
bool getPlayerDefaultAllowCustomNames() const;
bool getLoggingEnableLogging() const;
bool getDebugEnableDebuging() const;
};
  */
  REQUIRE(c.getPlayerDefaultDefaultNamePrefix() == "Player");
}