#ifndef DECK_H
#define DECK_H
#include <algorithm>
#include <array>
#include <chrono>
#include <random>
#include <string>

/// @brief Deck for the cards
class Deck {
private:
  std::array<std::string, 52> pile = {
      "A♣",  "2♣", "3♣",  "4♣", "5♣",  "6♣", "7♣", "8♣", "9♣", "10♣", "J♣",
      "Q♣",  "K♣", "A♦",  "2♦", "3♦",  "4♦", "5♦", "6♦", "7♦", "8♦",  "9♦",
      "10♦", "J♦", "Q♦",  "K♦", "A♥",  "2♥", "3♥", "4♥", "5♥", "6♥",  "7♥",
      "8♥",  "9♥", "10♥", "J♥", "Q♥",  "K♥", "A♠", "2♠", "3♠", "4♠",  "5♠",
      "6♠",  "7♠", "8♠",  "9♠", "10♠", "J♠", "Q♠", "K♠",
  };
  unsigned int position = 0;

public:
  /// @brief Will shuffle the deck on initialization.
  Deck();

  /// @brief determines if deck is empty.
  /// @return true when deck is empty.
  bool isEmpty() const;

  /// @brief Count of how many cards are left.
  /// @return an number of the cards left in the deck.
  unsigned int remaining() const;

  /// @brief Draws a card from the top of the deck
  /// @return will return a card from top of deck or will return "" on empty
  /// deck
  std::string draw();
};

#endif