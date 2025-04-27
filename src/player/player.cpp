#include "player.hpp"

Player::Player(const std::string &name, const std::set<Card> &initialHand) {
  if (name.empty())
    throw std::invalid_argument("Name cannot be empty");
  this->name = name;

  if (!initialHand.empty()) {
    for (auto card : initialHand) {
      if (card.isBlank())
        throw std::invalid_argument("No blank cards allowed.");
      hand.at(card.getValue()).push_back(card);
    }

    // moving cards to score if have all cards.
    for (auto &[key, val] : hand) {
      if (val.size() == 4) {
        val.clear();
        score++;
      }
    }
  }
}

bool Player::addCardToHand(const Card &card) {
  if (card.isBlank())
    return false;
  hand.at(card.getValue()).push_back(card);
  if (hand.at(card.getValue()).size() == 4) {
    hand.at(card.getValue()).clear(); // remove cards from hand
    score++;
  }
  return true;
}

std::vector<Card> Player::askForCards(const std::string &value) {
  auto subset = hand.find(value);
  // Invalid value
  if (subset == hand.end())
    return std::vector<Card>{};
  auto cards = hand.at(value);
  hand.at(value).clear(); // wipe cards
  return cards;
}

void Player::clearHand() {
  hand = {{"A", {}}, {"2", {}}, {"3", {}}, {"4", {}}, {"5", {}},
          {"6", {}}, {"7", {}}, {"8", {}}, {"9", {}}, {"10", {}},
          {"J", {}}, {"Q", {}}, {"K", {}}};
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

void Player::eliminatePlayer() { eliminated = true; }

unsigned short Player::getHandLength() const {
  unsigned short count = 0;
  for (const auto &[key, cards] : hand) {
    count += cards.size();
  }
  return count;
}

std::string Player::getName() const { return name; }

unsigned short Player::getScore() const { return score; }

bool Player::isEliminated() const { return eliminated; }
