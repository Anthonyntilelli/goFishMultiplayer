#include "deck.hpp"

void Deck::shuffle() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(pile.begin(), pile.end(), std::default_random_engine(seed));
}

Deck::Deck() { shuffle(); }

bool Deck::isEmpty() const { return pile.empty(); }

unsigned int Deck::remaining() const { return pile.size(); }

Card Deck::draw() {
  if (pile.empty())
    return Card{"", ""};

  auto card = pile.back();
  // Remove last element
  pile.pop_back();

  return card;
}

void Deck::putCardsBack(std::vector<Card> cards) {
  for (auto card : cards) {
    if (!card.isBlank())
      pile.push_back(card);
  }
  void shuffle();
}

void Deck::clear() { pile.clear(); }
