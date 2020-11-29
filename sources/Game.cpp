#include <iostream>

#include "Game.h"

void Game::draw() const {
  std::string text = "";
  int width = gameMap.getWidth();
  int height = gameMap.getHeight();

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {

      if (gameMap.get(x, y) == Map::Free) {
        if ((x == gameHero.x) && (y == gameHero.y)) {
          text += "┣┫";
        }
        else {
          int monsterCount = 0;
          for (const auto& m : gameMonsters) {
            if ((x == m.x) && (y == m.y)) { ++monsterCount; }
            if (monsterCount >= 2) { break; }
          }

          if (monsterCount == 1) { text += "M "; }
          else if (monsterCount > 1) { text += "MM"; }
          else { text += "░░"; }
        }
      }
      else { text += "██"; }
    }
    text += "\n";
  }

  std::cout << text;
}

void Game::setMap(Map map) {
  gameMap = map;
}

void Game::putHero(Hero hero, int x, int y) {
  if ((gameHero.x < 0) || (gameHero.y < 0)) {
    if (gameMap.get(x, y) == Map::Free) {
      gameHero.hero = hero;
      gameHero.x = x;
      gameHero.y = y;
    }
    else { std::cerr << "putting on wall exception" << std::endl; }
  }
  else { std::cerr << "hero already defined exception" << std::endl; }
}

void Game::putMonster(Monster monster, int x, int y) {
  if (gameMap.get(x, y) == Map::Free) {
    GameMonster temp;
    temp.monster = monster;
    temp.x = x;
    temp.y = y;
    gameMonsters.push_back(temp);
  }
}

void Game::run() {
  draw();
}
