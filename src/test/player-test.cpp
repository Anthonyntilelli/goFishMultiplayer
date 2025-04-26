//  Tests for player/player.hpp"
#include "../player/player.hpp"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Player is initalized correctly") {

  SECTION("Throws when expected") {
    REQUIRE_NOTHROW(Player{"James",
                           {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"),
                            Card("K", "♠"), Card("Q", "♥")}});
    REQUIRE_THROWS_AS((Player{"James",
                              {Card("A", "♦"), Card("", ""), Card("5", "♠"),
                               Card("K", "♠"), Card("Q", "♥")}}),
                      std::invalid_argument);
    REQUIRE_THROWS_AS((Player{"",
                              {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"),
                               Card("K", "♠"), Card("Q", "♥")}}),
                      std::invalid_argument);
  }

  SECTION("Valid Player set up created") {
    Player p{"James",
             {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"), Card("K", "♠"),
              Card("Q", "♥")}};
    REQUIRE(p.getName() == "James");
    REQUIRE(p.getScore() == 0);
    REQUIRE(p.getHandLength() == 5);
  }

  SECTION("Valid Player is set up with correct score") {
    Player p{"James",
             {Card("A", "♦"), Card("A", "♣"), Card("A", "♥"), Card("A", "♠"),
              Card("Q", "♥")}};
    REQUIRE(p.getName() == "James");
    REQUIRE(p.getScore() == 1);
    REQUIRE(p.getHandLength() == 1);
    REQUIRE(p.isEliminated() == false);
  }

  SECTION("Undefined player is created") {
    Player p{};
    REQUIRE(p.getName() == "Undefined");
    REQUIRE(p.getScore() == 0);
    REQUIRE(p.getHandLength() == 0);
    REQUIRE(p.isEliminated() == false);
  }
}
TEST_CASE("Player cards are added correctly") {
  Player p{"James",
           {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};

  SECTION("Base hand is 5") {
    REQUIRE(p.getHandLength() == 5);
    REQUIRE(p.isEmptyHand() == false);
  }

  SECTION("blank cards are rejected") {
    REQUIRE(p.addCardToHand(Card{"", ""}) == false);
    REQUIRE(p.getHandLength() == 5);
    REQUIRE(p.isEmptyHand() == false);
  }

  SECTION("Valid cards are taken") {
    REQUIRE(p.addCardToHand(Card{"K", "♦"}) == true);
    REQUIRE(p.getHandLength() == 6);
    REQUIRE(p.isEmptyHand() == false);
  }

  SECTION("When a match is made, all cards are remove and score goes up") {
    REQUIRE(p.addCardToHand(Card{"K", "♦"}) == true);
    REQUIRE(p.addCardToHand(Card{"K", "♥"}) == true);
    REQUIRE(p.addCardToHand(Card{"K", "♣"}) == true);
    REQUIRE(p.getHandLength() == 4);
    REQUIRE(p.isEmptyHand() == false);
    REQUIRE(p.getScore() == 1);
  }
}
TEST_CASE("Player cards are asked for correctly") {
  Player p{"James",
           {Card("A", "♦"), Card("A", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};
  REQUIRE(p.askForCards("3").empty() == true);
  REQUIRE(p.askForCards("A").size() == 2);
  REQUIRE(p.getHandLength() == 3);
  REQUIRE(p.askForCards("K").size() == 1);
  REQUIRE(p.getHandLength() == 2);
  // Ask for same cards again
  REQUIRE(p.askForCards("K").size() == 0);
  REQUIRE(p.getHandLength() == 2);

  REQUIRE(p.askForCards("INVALID").size() == 0);
  REQUIRE(p.getHandLength() == 2);
}
TEST_CASE("Player Hand is empty") {
  Player p{"James",
           {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};
  REQUIRE(p.isEmptyHand() == false);
  p.askForCards("A");
  p.askForCards("4");
  p.askForCards("5");
  p.askForCards("K");
  p.askForCards("Q");
  REQUIRE(p.isEmptyHand() == true);
}
TEST_CASE("Player GetHandLength is correct") {
  Player p1{"Bob", {Card("A", "♦"), Card("4", "♠"), Card("5", "♠")}};
  Player p2{"Alice", {}};

  REQUIRE(p1.getHandLength() == 3);
  REQUIRE(p2.getHandLength() == 0);

  p1.addCardToHand(Card{"A", "♠"});
  REQUIRE(p1.getHandLength() == 4);

  p1.addCardToHand(Card{"A", "♣"});
  p1.addCardToHand(Card{"A", "♥"});
  REQUIRE(p1.getHandLength() == 2);
  REQUIRE(p1.getScore() == 1);
}
TEST_CASE("Player Hand is a vector correctly") {
  Player p{"James",
           {Card("A", "♦"), Card("A", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};
  auto vec = p.toCardVector();
  REQUIRE(vec.size() == 5);

  bool found = (std::find(vec.begin(), vec.end(), Card("A", "♦")) != vec.end());
  REQUIRE(found);
}
TEST_CASE("Player name is correct") {
  Player p{"James",
           {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};
  REQUIRE(p.getName() == "James");
}
TEST_CASE("Player is eliminated correctly") {
  Player p{"James",
           {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};
  REQUIRE(p.isEliminated() == false);
  p.eliminatePlayer();
  REQUIRE(p.getHandLength() == 5);
  REQUIRE(p.isEliminated() == true);
}
TEST_CASE("Player clears hand correctly") {
  Player p{"James",
           {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};
  p.clearHand();
  REQUIRE(p.toCardVector().size() == 0);
  REQUIRE(p.isEmptyHand() == true);
}
// Player.getScore is implicitly tested in other test cases