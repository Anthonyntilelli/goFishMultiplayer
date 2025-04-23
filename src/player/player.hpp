#ifndef PLAYER_H
#define PLAYER_H
#include "../card/card.hpp"
#include <array>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

/// @brief PLayer in the go fish game, will contain name, hand, and score.
class Player {
private:
  std::map<std::string, std::array<Card, 4>> hand{
      {"A", {}}, {"2", {}}, {"3", {}}, {"4", {}}, {"5", {}},
      {"6", {}}, {"7", {}}, {"8", {}}, {"9", {}}, {"10", {}},
      {"J", {}}, {"Q", {}}, {"K", {}}};
  std::string name = "Undefined";
  unsigned short score = 0;

public:
  /// @brief Initialize the player.
  /// @throw throw an "invalid_argument" on incorrect values.
  /// @param name sets the players name. (cannot be "")
  /// @param initialHand set the players initial hand. (no blank cards)
  Player(const std::string &name, const std::set<Card> &initialHand);

  /// @brief Adds a card to the hand, and check if player has 4 of those cards,
  /// will remove those card from hand and increase if score so.
  /// @param card card to be added the hand.
  /// @return return false if care if a blank.
  bool addCardToHand(Card card);

  /// @brief Check if player has a value and return cards if they do.
  /// @param value the card value being asked for.
  /// @return return an array of cards matching the value or return empty array
  /// if no cards match.
  std::array<Card, 4> askForCards(std::string value);

  /// @brief Returns if the player's hand is empty.
  bool isEmptyHand() const;

  /// @brief Converts the players hand into a vector.
  /// @return return an array of cards.
  std::vector<Card> toCardVector() const;

  /// @brief Gets hand length.
  unsigned short getHandLength() const;

  /// @brief Gets player's name.
  std::string getName() const;

  /// @brief returns player score.
  unsigned short getScore() const;
};

#endif