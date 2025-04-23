//  Tests for card/card.hpp"
#include "../card/card.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Card initializes correctly") {
  REQUIRE_NOTHROW(Card{"", ""});
  REQUIRE_NOTHROW(Card{"A", "♣"});
  REQUIRE_THROWS_AS((Card{"99", "♣"}), std::invalid_argument);
  REQUIRE_THROWS_AS((Card{"A", "B"}), std::invalid_argument);
}
TEST_CASE("Correct value and suit is returned") {
  Card c{"A", "♣"};
  REQUIRE(c.isBlank() == false);
  REQUIRE(c.getValue() == "A");
  REQUIRE(c.getSuit() == "♣");
}
TEST_CASE("Card is correctly blank") {
  Card blank{"", ""};
  REQUIRE(blank.isBlank() == true);
  REQUIRE(blank.getSuit().empty());
  REQUIRE(blank.getValue().empty());
}

TEST_CASE("Card Operators are working correctly") {
  Card a{"A", "♣"};
  Card b{"A", "♣"};
  Card c{"3", "♣"};
  REQUIRE(a == b);
  REQUIRE(a != c);
  REQUIRE(c < a);
}