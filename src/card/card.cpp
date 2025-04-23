#include "card.hpp"

Card::Card(const std::string &value, const std::string &suit) {
  // blank card
  if (value.empty() && suit.empty())
    return;
  const std::unordered_set<std::string> validValues = {
      "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
  };
  const std::unordered_set<std::string> validSuits = {"♣", "♦", "♥", "♠"};
  if (!validValues.contains(value))
    throw std::invalid_argument("Invalid value of " + value);
  if (!validSuits.contains(suit))
    throw std::invalid_argument("Invalid suit of " + suit);
  this->value = value;
  this->suit = suit;
}

std::string Card::getValue() const { return value; }

std::string Card::getSuit() const { return suit; }

bool Card::isBlank() const { return (value.empty() && suit.empty()); }
