#include "player.hpp"

Player::Player(const std::string &name, const std::set<Card> &initialHand) {
  if (name.empty())
    throw std::invalid_argument("Name cannot be empty");
  this->name = name;

  if (!initialHand.empty()) {
    for (auto card : initialHand) {
      if (card.isBlank())
        throw std::invalid_argument("No blank cards allowed.");
      hand.at(card.getValue()).at(hand.at(card.getValue()).size()) = card;
    }

    // moving cards to score if have all cards.
    for (auto &[key, val] : hand) {
      if (val.size() == 4) {
        val = {};
        score++;
      }
    }
  }
}

bool Player::addCardToHand(Card card) {
  if (card.isBlank())
    return false;
  hand.at(card.getValue()).at(hand.at(card.getValue()).size()) = card;
  if (hand.at(card.getValue()).size() == 4) {
    hand.at(card.getValue()) = {};
    score++;
  }
  return true;
}

std::array<Card, 4> Player::askForCards(std::string value) {
  auto subset = hand.find(value);
  // Invalid value
  if (subset == hand.end())
    return std::array<Card, 4>{};
  auto cards = hand.at(value);
  hand.at(value) = std::array<Card, 4>{};
  return cards;
}

bool Player::isEmptyHand() const { return getHandLength() == 0; }

std::vector<Card> Player::toCardVector() const {
  std::vector<Card> returnVal{};
  for (auto &[_, cards] : hand) {
    for (auto card : cards) {
      returnVal.push_back(card);
    }
  }
  return returnVal;
}

unsigned short Player::getHandLength() const {
  unsigned short count = 0;
  for (const auto &[key, cards] : hand) {
    count = +cards.size();
  }
  return count;
}

std::string Player::getName() const { return name; }

unsigned short Player::getScore() const { return score; }
