#include "table.hpp"

bool Table::addPlayer(Player &player) {
  if (player.getName() == "Undefined")
    return false;
  if (gameStarted)
    return false;
  // Player with that name already exits.
  if (players.find(player.getName()) != players.end())
    return false;

  if (player.getHandLength() != 0)
    return false;

  if (players.size() == 6)
    return false;

  // Add 5 cards to hand
  player.addCardToHand(deck.draw());
  player.addCardToHand(deck.draw());
  player.addCardToHand(deck.draw());
  player.addCardToHand(deck.draw());
  player.addCardToHand(deck.draw());

  players[player.getName()] = player;
  rotation.push_back(player.getName());
  return true;
}

bool Table::startGame() {
  if (players.size() < 2)
    return false;
  gameStarted = true;
  return true;
}

TableMessage Table::askOtherPlayerForCards(const std::string &cardValue,
                                           const std::string &playerName) {
  auto returnVal = TableMessage{};
  if (!players.contains(playerName)) {
    returnVal.message = "Player " + playerName + " does not exist.";
    returnVal.error = true;
    return returnVal;
  }
  if (players.at(playerName).isEliminated()) {
    returnVal.message = "Player " + playerName + " is eliminated.";
    returnVal.error = true;
    return returnVal;
  }

  if (rotation.at(turn) == playerName) {
    returnVal.message = "Player cannot name themself as the other player.";
    returnVal.error = true;
    return returnVal;
  }

  auto currentPlayer = &players.at(rotation.at(turn));
  auto otherPlayer = &players.at(playerName);
  auto cards = otherPlayer->askForCards(cardValue);
  // go fish
  if (cards.empty()) {
    currentPlayer->addCardToHand(deck.draw());
    returnVal.message = currentPlayer->getName() + " had to go fish.";
    returnVal.error = false;
  } else {
    for (auto card : cards)
      currentPlayer->addCardToHand(card);
    returnVal.message =
        currentPlayer->getName() + " took the cards from " + playerName;
    returnVal.error = false;
  }
  turn = (turn + 1) % rotation.size();
  return returnVal;
}

bool Table::eliminatePlayer(const std::string &name) {
  if (!players.contains(name))
    return false;
  auto cards = players.at(name).toCardVector();
  players.at(name).clearHand();
  players.at(name).eliminatePlayer();
  deck.putCardsBack(cards);

  // REMOVE user from rotation
  auto start = std::remove(rotation.begin(), rotation.end(), name);
  rotation.erase(start, rotation.end());
  return true;
}

const Player Table::getPlayer(const std::string &name) const {
  if (players.contains(name))
    return players.at(name);
  return Player();
}

std::string Table::whoTurn() const {
  if (!gameStarted)
    return "";
  if (!rotation.empty())
    return rotation.at(turn);
  return "";
}

unsigned short Table::getPlayerCount() const { return rotation.size(); }

bool Table::isGameStarted() const { return gameStarted; }

bool Table::isGameOver() const {
  if (deck.isEmpty())
    return true;
  if (rotation.size() <= 1 && isGameStarted())
    return true;
  return false;
}

std::string Table::getWinner() const {
  if (!isGameOver())
    return "";
  if (players.empty())
    return "";
  std::map<int, std::vector<std::string>> scoreList{};
  for (const auto [_, player] : players) {
    if (!scoreList.contains(player.getScore())) {
      scoreList[player.getScore()] = {};
    }
    scoreList.at(player.getScore()).push_back(player.getName());
  }
  std::string winners{};
  for (const auto name : scoreList.crbegin()->second) {
    winners += (name + ", ");
  }

  if (!winners.empty()) {
    winners.erase(winners.size() - 2); // Remove the last ", "
  }
  return winners;
}

// TEST
void test::emptyDeck(Table &t) { t.deck.clear(); }
void test::forcePlayerWin(Table &t, const std::string &name) {
  while (!t.deck.isEmpty()) {
    t.players.at(name).addCardToHand(t.deck.draw());
  }
}
void test::forcePlayerTie(Table &t) {
  if (!t.rotation.empty())
    throw std::invalid_argument("table t is not empty");
  if (t.deck.remaining() != 52)
    throw std::invalid_argument("table t is missing cards");

  std::set<Card> pile1 = {
      Card{"A", "♣"}, Card{"A", "♦"}, Card{"A", "♥"}, Card{"A", "♠"},
      Card{"2", "♣"}, Card{"2", "♦"}, Card{"2", "♥"}, Card{"2", "♠"},
      Card{"3", "♣"}, Card{"3", "♦"}, Card{"3", "♥"}, Card{"3", "♠"},
      Card{"4", "♣"}, Card{"4", "♦"}, Card{"4", "♥"}, Card{"4", "♠"}};
  std::set<Card> pile2 = {
      Card{"5", "♣"}, Card{"5", "♦"}, Card{"5", "♥"}, Card{"5", "♠"},
      Card{"6", "♣"}, Card{"6", "♦"}, Card{"6", "♥"}, Card{"6", "♠"},
      Card{"7", "♣"}, Card{"7", "♦"}, Card{"7", "♥"}, Card{"7", "♠"},
      Card{"8", "♣"}, Card{"8", "♦"}, Card{"8", "♥"}, Card{"8", "♠"}};
  std::set<Card> pile3 = {Card{"5", "♣"}, Card{"5", "♦"}, Card{"5", "♥"},
                          Card{"5", "♠"}};

  Player a{"alice", pile1};
  t.players["alice"] = a;
  t.rotation.push_back("alice");

  Player b{"bob", pile2};
  t.players["bob"] = b;
  t.rotation.push_back("bob");

  Player c{"gary", pile3};
  t.players["gary"] = c;
  t.rotation.push_back("gary");
  t.startGame();
}
