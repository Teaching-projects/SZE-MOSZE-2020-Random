#ifndef GAME_H
#define GAME_H

#include <string>
#include <list>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"

class Game {
  struct GameMonster {
    Monster monster;
    int x = -1;
    int y = -1;
  };
  struct GameHero {
    Hero hero;
    int x = -1;
    int y = -1;
  };

  Map gameMap;
  GameHero gameHero;
  std::list<GameMonster> gameMonsters;

  void draw() const;

public:
  Game() {}
  Game(const std::string& mapfilename) : gameMap(Map(mapfilename)) {}

  void setMap(Map map);
  void putHero(Hero hero, int x, int y);
  void putMonster(Monster monster, int x, int y);
  void run();
};

#endif
