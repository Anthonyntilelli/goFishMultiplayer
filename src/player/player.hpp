#ifndef PLAYER_H
#define PLAYER_H
#include "../card/card.hpp"
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

/// @brief PLayer in the go fish game, will contain name, hand, and score.
class Player {
private:
  std::map<std::string, std::vector<Card>> hand{
      {"A", {}}, {"2", {}}, {"3", {}}, {"4", {}}, {"5", {}},
      {"6", {}}, {"7", {}}, {"8", {}}, {"9", {}}, {"10", {}},
      {"J", {}}, {"Q", {}}, {"K", {}}};
  std::string name{"Undefined"};
  unsigned short score{0};
  bool eliminated{false};

public:
  /// @brief Creates Undefined player.
  Player() = default;

  /// @brief Initialize the player.
  /// @throw throw an "invalid_argument" on incorrect values.
  /// @param name sets the players name. (cannot be "")
  /// @param initialHand A set of cards to initialize the player's hand. Must
  /// not contain blank cards.
  Player(const std::string &name, const std::set<Card> &initialHand);

  /// @brief Adds a card to the hand, and check if player has 4 of those cards,
  /// will remove those card from hand and increase if score so.
  /// @param card card to be added the hand.
  /// @return return false if care if a blank.
  bool addCardToHand(const Card &card);

  /// @brief Check if player has a value and return cards if they do. Cards
  /// returned are removed from players hand.
  /// @param value the card value being asked for.
  /// @return return an vector of cards matching the value or return empty
  /// vector if no cards match.
  std::vector<Card> askForCards(const std::string &value);

  /// @brief clears player's hand, back to inital state.
  void clearHand();

  /// @brief Returns if the player's hand is empty.
  bool isEmptyHand() const;

  /// @brief Converts the players hand into a vector.
  /// @return return an vector of cards.
  std::vector<Card> toCardVector() const;

  /// @brief Eliminates a player.
  void eliminatePlayer();

  /// @brief Gets hand length.
  unsigned short getHandLength() const;

  /// @brief Gets player's name.
  std::string getName() const;

  /// @brief returns player score.
  unsigned short getScore() const;

  /// @brief returns if player is eliminated.
  bool isEliminated() const;
};

#endif