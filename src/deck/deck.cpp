#include "deck.hpp"

Deck::Deck() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(pile.begin(), pile.end(), std::default_random_engine(seed));
}

bool Deck::isEmpty() const { return position == 52; }

unsigned int Deck::remaining() const { return 52 - position; }

std::string Deck::draw() {
  if (position == 52)
    return "";
  auto card = pile.at(position);
  position++;
  return card;
}
