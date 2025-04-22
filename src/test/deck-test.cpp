//  Tests for deck/deck.hpp"
#include "../deck/deck.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Deck initializes correctly") {
  Deck d{};

  REQUIRE(d.isEmpty() == false);
  REQUIRE(d.remaining() == 52);
  REQUIRE(d.draw() != "");
}

TEST_CASE("Deck shuffles correctly") {
  Deck a{};
  Deck b{};
  Deck c{};

  auto draw1 = a.draw();
  auto draw2 = b.draw();
  auto draw3 = c.draw();

  REQUIRE(draw1 != "");
  REQUIRE(draw2 != "");
  REQUIRE(draw3 != "");
  REQUIRE(draw1 != draw2);
  REQUIRE(draw1 != draw3);
}
TEST_CASE("Draw works correctly") {
  Deck d{};
  SECTION("Draw does not repeat") {
    auto card1 = d.draw();
    auto card2 = d.draw();
    REQUIRE(card1 != card2);
    REQUIRE(d.isEmpty() == false);
    REQUIRE(d.remaining() == 50);
  }
  SECTION("Draw give empty when deck is empty") {
    std::string card;
    for (int i = 1; i <= 52; i++) {
      card = d.draw();
      REQUIRE(d.remaining() == (52 - i));
    }
    REQUIRE(card != "");
    REQUIRE(d.isEmpty() == true);
    REQUIRE(d.remaining() == 0);
    // Draw past last card
    REQUIRE(d.draw().empty());
    REQUIRE(d.isEmpty() == true);
    REQUIRE(d.remaining() == 0);
  }
}