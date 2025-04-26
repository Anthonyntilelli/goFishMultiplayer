//  Tests for deck/deck.hpp"
#include "../deck/deck.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Deck initializes correctly") {
  Deck d{};

  REQUIRE(d.isEmpty() == false);
  REQUIRE(d.remaining() == 52);
  REQUIRE(d.draw().isBlank() == false);
}

TEST_CASE("Deck shuffles correctly") {
  Deck a{};
  Deck b{};
  Deck c{};

  auto draw1 = a.draw();
  auto draw2 = b.draw();
  auto draw3 = c.draw();

  REQUIRE(draw1.isBlank() == false);
  REQUIRE(draw2.isBlank() == false);
  REQUIRE(draw3.isBlank() == false);
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
    Card card;
    for (int i = 1; i <= 52; i++) {
      card = d.draw();
      REQUIRE(d.remaining() == (52 - i));
    }
    REQUIRE(card.isBlank() == false);
    REQUIRE(d.isEmpty() == true);
    REQUIRE(d.remaining() == 0);
    // Draw past last card
    REQUIRE(d.draw().isBlank());
    REQUIRE(d.isEmpty() == true);
    REQUIRE(d.remaining() == 0);
  }
}

TEST_CASE("Deck pushes cards back correctly") {
  Deck d{};
  auto card1 = d.draw();
  auto card2 = d.draw();
  auto card3 = d.draw();

  REQUIRE(d.remaining() == 49);
  d.putCardsBack({card1, card2, card3});
  REQUIRE(d.remaining() == 52);
  d.putCardsBack({Card{}});
  REQUIRE(d.remaining() == 52);
}

TEST_CASE("Deck is cleared correctly") {
  Deck d{};
  REQUIRE(d.isEmpty() == false);
  d.clear();
  REQUIRE(d.isEmpty() == true);
}
