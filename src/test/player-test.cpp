//  Tests for player/player.hpp"
#include "../player/player.hpp"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
/*
A 2 3 4 5 6 7 8 9 10 K J Q
"♦","♣","♥","♠"
*/

TEST_CASE("Player is initalized correctly") {
  Player p{"James",
           {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};
  Player p2{"James",
            {Card("A", "♦"), Card("A", "♣"), Card("A", "♥"), Card("A", "♠"),
             Card("Q", "♥")}};
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

  REQUIRE(p.getName() == "James");
  REQUIRE(p.getScore() == 0);
  REQUIRE(p.getHandLength() == 5);

  REQUIRE(p2.getName() == "James");
  REQUIRE(p2.getScore() == 1);
  REQUIRE(p2.getHandLength() == 1);
}
TEST_CASE("Player cards are added correctly") {
  Player p{"James",
           {Card("A", "♦"), Card("4", "♠"), Card("5", "♠"), Card("K", "♠"),
            Card("Q", "♥")}};

  REQUIRE(p.getHandLength() == 5);
  REQUIRE(p.isEmptyHand() == false);

  REQUIRE(p.addCardToHand(Card{"", ""}) == false);
  REQUIRE(p.getHandLength() == 5);
  REQUIRE(p.isEmptyHand() == false);

  REQUIRE(p.addCardToHand(Card{"K", "♦"}) == true);
  REQUIRE(p.getHandLength() == 6);
  REQUIRE(p.isEmptyHand() == false);

  REQUIRE(p.addCardToHand(Card{"K", "♥"}) == true);
  REQUIRE(p.addCardToHand(Card{"K", "♣"}) == true);
  REQUIRE(p.getHandLength() == 2);
  REQUIRE(p.isEmptyHand() == false);
  REQUIRE(p.getScore() == 1);
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
// Player.getHandLength is implicitly tested in other test cases
// Player.getScore is implicitly tested in other test cases