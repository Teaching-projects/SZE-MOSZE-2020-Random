#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"

class Game {
public:
  class OccupiedException : public std::exception {
  public:
    ~OccupiedException() throw() {}
    const char* what() const throw() { return "Position already occupied."; }
  };

  class AlreadyHasHeroException : public std::exception {
  public:
    ~AlreadyHasHeroException() throw() {}
    const char* what() const throw() { return "Hero already defined."; }
  };

  class AlreadyHasUnitsException : public std::exception {
  public:
    ~AlreadyHasUnitsException() throw() {}
    const char* what() const throw() { return "Units already defined."; }
  };

  class NotInitializedException : public std::exception {
  public:
    ~NotInitializedException() throw() {}
    const char* what() const throw() { return "Game elements are not initialized."; }
  };

  class GameAlreadyStartedException : public std::exception {
  public:
    ~GameAlreadyStartedException() throw() {}
    const char* what() const throw() { return "The game already started."; }
  };

  class PuttingOnWallException : public std::exception {
  public:
    ~PuttingOnWallException() throw() {}
    const char* what() const throw() { return "Tried to put units on the wall."; }
  };

private:
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
  std::vector<GameMonster> gameMonsters;

  bool running = false;

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
