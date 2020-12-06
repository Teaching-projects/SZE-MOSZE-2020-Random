#ifndef PREPAREDGAME_H
#define PREPAREDGAME_H

#include "Game.h"

class PreparedGame : public Game {
  using Game::setMap;
  using Game::putHero;
  using Game::putMonster;
  using Game::hasHero;

public:
  explicit PreparedGame(const std::string& filename);
};

#endif
