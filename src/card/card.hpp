#ifndef CARD_H
#define CARD_H
#include <stdexcept>
#include <string>
#include <unordered_set>

/// @brief Represents a standard playing card.
class Card {
private:
  std::string value{};
  std::string suit{};

public:
  /// @brief Creates a blank card
  Card() = default;

  /// @brief Initializes the card with value and suit
  /// @throw throw an "invalid_argument" on incorrect values.
  /// @param value sets the value of the card.
  /// @param suit sets the suit of the card.
  Card(const std::string &value, const std::string &suit);

  /// @brief Return the value of the card.
  /// @return "" if the card is blank.
  std::string getValue() const;

  /// @brief Return the suit of a card.
  /// @return "" if the card is blank.
  std::string getSuit() const;

  /// @brief Return true if a card is blank.
  bool isBlank() const;

  /// @brief Check for equality of a pair of cards.
  friend inline bool operator==(const Card &lhs, const Card &rhs) {
    return (lhs.value == rhs.value) && (lhs.suit == rhs.suit);
  }

  /// @brief Check for inequality of a pair of cards.
  friend inline bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);
  }
  // Add operator< for ordering
  bool operator<(const Card &other) const {
    // First compare by suit, then by rank
    if (suit != other.suit)
      return suit < other.suit;
    return value < other.value;
  }
};
#endif
