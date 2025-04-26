//  Tests for table/table.hpp"
#include "../table/table.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("TableMessage has correct defaults") {
  TableMessage t{};
  REQUIRE(t.error == false);
  REQUIRE(t.message.empty() == true);
}
TEST_CASE("Table defaults correctly") {
  Table t{};
  REQUIRE(t.getPlayer("bob").getName() == "Undefined");
  REQUIRE(t.whoTurn().empty());
  REQUIRE(t.getPlayerCount() == 0);
  REQUIRE(t.isGameStarted() == false);
  REQUIRE(t.isGameOver() == false);
  REQUIRE(t.getWinner().empty());
}
TEST_CASE("Table starts game correctly") {
  Table t{};
  SECTION("Table game does not start with 1 player") {
    auto bob = Player{"bob", {}};
    t.addPlayer(bob);
    REQUIRE(t.startGame() == false);
    REQUIRE(t.isGameStarted() == false);
  }
  SECTION("Table game starts correct with 2 players") {
    auto bob = Player{"bob", {}};
    auto alice = Player("alice", {});
    t.addPlayer(bob);
    t.addPlayer(alice);
    REQUIRE(t.startGame() == true);
    REQUIRE(t.isGameStarted() == true);
  }
  SECTION("Table game starts correct with 6 players") {
    auto bob = Player{"bob1", {}};
    auto alice = Player("alice1", {});
    auto bob2 = Player{"bob2", {}};
    auto alice2 = Player("alice2", {});
    auto bob3 = Player{"bob3", {}};
    auto alice3 = Player("alice3", {});
    t.addPlayer(bob);
    t.addPlayer(alice);
    t.addPlayer(bob2);
    t.addPlayer(alice2);
    t.addPlayer(bob3);
    t.addPlayer(alice3);
    REQUIRE(t.startGame() == true);
    REQUIRE(t.isGameStarted() == true);
  }
}
TEST_CASE("Table askOtherPlayerForCards correctly.") {
  Table t{};
  auto bob = Player{"bob1", {}};
  auto alice = Player("alice1", {});
  auto bob2 = Player{"bob2", {}};
  auto alice2 = Player("alice2", {});
  auto bob3 = Player{"bob3", {}};
  auto alice3 = Player("alice3", {});
  t.addPlayer(bob);
  t.addPlayer(alice);
  t.addPlayer(bob2);
  t.addPlayer(alice2);
  t.addPlayer(bob3);
  t.addPlayer(alice3);
  t.eliminatePlayer("alice3");
  t.startGame();

  SECTION("Ask for a person that does not exist or eliminated") {
    auto tm1 = t.askOtherPlayerForCards("A", "Invalid");
    REQUIRE(tm1.message == "Player Invalid does not exist.");
    REQUIRE(tm1.error == true);
    REQUIRE(t.whoTurn() == "bob1");
    auto tm2 = t.askOtherPlayerForCards("A", "alice3");
    REQUIRE(tm1.message == "Player Invalid does not exist.");
    REQUIRE(tm1.error == true);
    REQUIRE(t.whoTurn() == "bob1");
  }
  SECTION("Ask for card from themself") {
    REQUIRE(t.whoTurn() == "bob1");
    auto tm1 = t.askOtherPlayerForCards("A", "bob1");
    REQUIRE(tm1.message == "Player cannot name themself as the other player.");
    REQUIRE(tm1.error == true);
    REQUIRE(t.whoTurn() == "bob1");
  }
  SECTION("Ask for card that does exits (in players hand)") {
    auto card = t.getPlayer("alice1").toCardVector()[0];
    auto preCount = t.getPlayer("alice1").toCardVector().size();
    auto tm1 = t.askOtherPlayerForCards(card.getValue(), "alice1");
    REQUIRE(tm1.message == "bob1 took the cards from alice1");
    REQUIRE(tm1.error == false);
    REQUIRE(t.whoTurn() == "alice1");
    REQUIRE(preCount > t.getPlayer("alice1").toCardVector().size());
  }
  SECTION("Ask for card that does not exist") {
    REQUIRE(t.whoTurn() == "bob1");
    auto tm1 = t.askOtherPlayerForCards("INVALID", "bob2");
    REQUIRE(tm1.message == "bob1 had to go fish.");
    REQUIRE(tm1.error == false);
    REQUIRE(t.whoTurn() == "alice1");
  }
}
TEST_CASE("Table eliminatePlayer correctly") {
  Table t{};
  auto bob = Player{"bob1", {}};
  auto alice = Player("alice1", {});
  auto bob2 = Player{"bob2", {}};
  auto alice2 = Player("alice2", {});
  auto bob3 = Player{"bob3", {}};
  auto alice3 = Player("alice3", {});
  t.addPlayer(bob);
  t.addPlayer(alice);
  t.addPlayer(bob2);
  t.addPlayer(alice2);
  t.addPlayer(bob3);
  t.addPlayer(alice3);

  SECTION("Cannot eliminate player that does not exits") {
    REQUIRE(t.eliminatePlayer("POTATO") == false);
  }
  SECTION("Player is eliminated") {
    REQUIRE(t.eliminatePlayer("alice1") == true);
    REQUIRE(t.getPlayer("alice1").isEliminated() == true);
    REQUIRE(t.getPlayer("alice1").getHandLength() == 0);
  }
}
TEST_CASE("Table getPlayer works correctly") {
  Table t{};
  auto bob = Player{"bob", {}};
  auto alice = Player("alice", {});
  t.addPlayer(bob);
  t.addPlayer(alice);
  REQUIRE(t.getPlayer("alice").getName() == "alice");
  REQUIRE(t.getPlayer("bob").getName() == "bob");
  REQUIRE(t.getPlayer("APPLE").getName() == "Undefined");
}
TEST_CASE("Table displays whoTurn correctly") {
  Table t{};
  auto bob = Player{"bob", {}};
  auto alice = Player("alice", {});
  t.addPlayer(bob);
  t.addPlayer(alice);
  SECTION("No Ones turn if game not started") {
    REQUIRE(t.whoTurn() == "");
    REQUIRE(t.isGameStarted() == false);
  }
  SECTION("turn is displayed when game is started") {
    t.startGame();
    REQUIRE(t.isGameStarted() == true);
    REQUIRE(t.whoTurn() == "bob");
  }
  SECTION("Turn is not displayed if no players are on table") {
    Table t2{};
    REQUIRE(t2.whoTurn().empty() == true);
  }
}
TEST_CASE("Table getPlayerCount correctly") {
  Table t{};
  REQUIRE(t.getPlayerCount() == 0);
  auto bob = Player{"bob", {}};
  auto alice = Player("alice", {});
  t.addPlayer(bob);
  t.addPlayer(alice);
  REQUIRE(t.getPlayerCount() == 2);
}
TEST_CASE("Table returns isGameStarted correctly") {
  Table t{};
  REQUIRE(t.isGameStarted() == false);
  REQUIRE(t.startGame() == false);

  auto bob = Player{"bob", {}};
  auto alice = Player("alice", {});
  t.addPlayer(bob);
  t.addPlayer(alice);
  REQUIRE(t.startGame() == true);
  REQUIRE(t.isGameStarted() == true);
}
TEST_CASE("Table states gameOver correctly") {
  Table t{};
  auto bob = Player{"bob", {}};
  auto alice = Player("alice", {});
  t.addPlayer(bob);
  t.addPlayer(alice);
  t.startGame();

  SECTION("gameOver on empty deck") {
    REQUIRE(t.isGameOver() == false);
    emptyDeck(t);
    REQUIRE(t.isGameOver() == true);
  }

  SECTION("gameOver when player eliminated") {
    t.eliminatePlayer("bob");
    REQUIRE(t.isGameOver() == true);
  }
}
TEST_CASE("Table returns the correct winner") {
  Table t{};
  auto bob = Player{"bob", {}};
  auto alice = Player("alice", {});
  t.addPlayer(bob);
  t.addPlayer(alice);

  SECTION("GAME not over") {
    REQUIRE(t.isGameOver() == false);
    REQUIRE(t.getWinner().empty() == true);
  }
  SECTION("GAME is a tie") {
    Table t2{};
    forcePlayerTie(t2);
    emptyDeck(t2);
    REQUIRE(t2.getPlayer("alice").getScore() == 4);
    REQUIRE(t2.getPlayer("bob").getScore() == 4);
    REQUIRE(t2.getPlayer("Gary").getScore() == 1);
    REQUIRE(t2.isGameOver() == true);
    REQUIRE(t2.getWinner() == "alice, bob");
  }
  SECTION("Game has only one winner") {
    t.startGame();
    forcePlayerWin(t, "bob");
    emptyDeck(t);
    REQUIRE(t.isGameOver() == true);
    REQUIRE(t.getWinner() == "bob");
  }
}
