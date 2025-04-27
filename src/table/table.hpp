#ifndef TABLE_H
#define TABLE_H
#include "../deck/deck.hpp"
#include "../player/player.hpp"
#include <algorithm>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

/// @brief Struct used by as TABLE::askOtherPlayerForCards()
struct TableMessage {
  /// @brief Constains the message results.
  std::string message{};
  /// @brief if true the message is an error.
  bool error{false};
};

/// @brief Table where game is played.
class Table {
private:
  std::unordered_map<std::string, Player> players{};
  std::vector<std::string> rotation{};
  Deck deck{};
  unsigned short turn{0};
  bool gameStarted{false};

public:
  /// @brief Adds player to the table and hands them 5 cards. Players cannot be
  /// added if game is started. Table max is 6.
  /// @param player player to be added to table. Player with existing cards or
  /// duplicate name will be rejected.
  /// @return true if player is added and false if player was rejected.
  bool addPlayer(Player &player);

  /// @brief starts the game.
  /// @return false if game cannot start, less then 2 players
  bool startGame();

  /// @brief The Players who turn it is can ask player for cards. Turn is ended
  /// on this call. Turn does not end on error.
  /// @param cardValue value of the card to ask for.
  /// @param playerName name of player to ask, do not put in "" or your own
  /// name.
  /// @return a message if successful or an error.
  TableMessage askOtherPlayerForCards(const std::string &cardValue,
                                      const std::string &playerName);

  /// @brief eliminate the player and puts their hand back in the deck.
  /// @param name of player to eliminate.
  /// @return true when player is eliminated or false if player does not exist.
  bool eliminatePlayer(const std::string &name);

  /// @brief Return a player by name
  /// @param name players name to return
  /// @return the player if found or an "Undefined" player if cannot find.
  const Player getPlayer(const std::string &name) const;

  /// @brief Name of player who turn it is.
  /// @return return name of player or "" no players on rotation or game not
  /// started
  std::string whoTurn() const;

  /// @brief Returns player count.
  unsigned short getPlayerCount() const;

  /// @brief Returns if game has started.
  bool isGameStarted() const;

  /// @brief Return if game is over.
  /// Deck is empty or only one player is not eliminated.
  bool isGameOver() const;

  /// @brief Return the name of the winner. Eliminated players cannot be a
  /// winner.
  /// @return name of the winning player or "" if game is still running.
  /// Multiple names are returned on ties.
  std::string getWinner() const;

  /// @brief [Debug method] empty players deck.
  /// @param t table with players.
  friend void emptyDeck(Table &t);

  /// @brief [Debug method] make a player the winner.
  /// @param t table player.
  /// @param name name of winning player.
  friend void forcePlayerWin(Table &t, const std::string &name);

  ///@brief [Debug method] forces a player tie and startsGame.
  ///@param t empty table only.
  friend void forcePlayerTie(Table &t);
};

#endif