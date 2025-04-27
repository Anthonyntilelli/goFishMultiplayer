#ifndef DECK_H
#define DECK_H
#include "../card/card.hpp"
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

/// @brief Deck of standard playing card represented as an array of cards
class Deck {
private:
  std::vector<Card> pile{
      Card{"A", "♣"},  Card{"2", "♣"},  Card{"3", "♣"},  Card{"4", "♣"},
      Card{"5", "♣"},  Card{"6", "♣"},  Card{"7", "♣"},  Card{"8", "♣"},
      Card{"9", "♣"},  Card{"10", "♣"}, Card{"J", "♣"},  Card{"Q", "♣"},
      Card{"K", "♣"},  Card{"A", "♦"},  Card{"2", "♦"},  Card{"3", "♦"},
      Card{"4", "♦"},  Card{"5", "♦"},  Card{"6", "♦"},  Card{"7", "♦"},
      Card{"8", "♦"},  Card{"9", "♦"},  Card{"10", "♦"}, Card{"J", "♦"},
      Card{"Q", "♦"},  Card{"K", "♦"},  Card{"A", "♥"},  Card{"2", "♥"},
      Card{"3", "♥"},  Card{"4", "♥"},  Card{"5", "♥"},  Card{"6", "♥"},
      Card{"7", "♥"},  Card{"8", "♥"},  Card{"9", "♥"},  Card{"10", "♥"},
      Card{"J", "♥"},  Card{"Q", "♥"},  Card{"K", "♥"},  Card{"A", "♠"},
      Card{"2", "♠"},  Card{"3", "♠"},  Card{"4", "♠"},  Card{"5", "♠"},
      Card{"6", "♠"},  Card{"7", "♠"},  Card{"8", "♠"},  Card{"9", "♠"},
      Card{"10", "♠"}, Card{"J", "♠"},  Card{"Q", "♠"},  Card{"K", "♠"}};

  void shuffle();

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
  /// @return will return a card from top of deck or will return blank card on
  /// empty deck
  Card draw();

  /// @brief Adds cards back into the deck and re-shuffles the deck.
  /// @param cards cards to put back into deck, blank cards would be removed.
  void putCardsBack(std::vector<Card> cards);

  /// @brief emptys the deck
  void clear();
};

#endif