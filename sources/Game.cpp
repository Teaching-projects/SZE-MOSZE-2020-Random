#include "Game.h"

Game::~Game() {
  for (auto& r : renderers) {
    delete r;
  }
}

void Game::setMap(const Map& map) {
  if (running) { throw GameAlreadyStartedException(); }

  if ((gameHero.x < 0) && (gameHero.y < 0) && (gameMonsters.size() == 0)) {
    gameMap = map;
  }
  else {
    throw AlreadyHasUnitsException();
  }
}

void Game::putHero(const Hero& hero, int x, int y) {
  if (running) { throw GameAlreadyStartedException(); }

  if ((gameMap.getWidth() <= 0) || (gameMap.getHeight() <= 0)) {
    throw Map::WrongIndexException();
  }

  if ((gameHero.x < 0) || (gameHero.y < 0)) {
    if (gameMap.get(x, y) == Map::Free) {
      gameHero.hero = hero;
      gameHero.x = x;
      gameHero.y = y;
    }
    else { throw OccupiedException(); }
  }
  else { throw AlreadyHasHeroException(); }
}

void Game::putMonster(const Monster& monster, int x, int y) {
  if (running) { throw GameAlreadyStartedException(); }

  if ((gameMap.getWidth() <= 0) || (gameMap.getHeight() <= 0)) {
    throw Map::WrongIndexException();
  }

  if (gameMap.get(x, y) == Map::Free) {
    GameMonster temp;
    temp.monster = monster;
    temp.x = x;
    temp.y = y;
    gameMonsters.push_back(temp);
  }
  else { throw OccupiedException(); }
}

void Game::registerRenderer(Renderer* renderer) {
  renderers.push_back(renderer);
}

void Game::run(std::istream& is) {
  if (running) { throw GameAlreadyStartedException(); }

  if (!gameHero.hero.isAlive() || (gameHero.x < 0) || (gameHero.y < 0) || (gameMonsters.size() == 0)) {
    throw NotInitializedException();
  }

  running = true;
  while (running) {
    for (int i = 0; (i < (int)gameMonsters.size()) && running;) {
      GameMonster m = gameMonsters[i];

      if ((m.x == gameHero.x) && (m.y == gameHero.y)) {
        gameHero.hero.fightTilDeath(m.monster);

        if (!m.monster.isAlive()) {
          gameMonsters.erase(gameMonsters.begin() + i);
        }
        else { running = false; }
      }
      else { ++i; }
    }

    for (const auto& r : renderers) {
      r->render(*this);
    }

    if (running) {
      if (gameMonsters.size() == 0) {
        running = false;
        std::cout << gameHero.hero.getName() << " cleared the map." << std::endl;
      }
    }
    else {
      gameHero.x = -1;
      gameHero.y = -1;
      std::cout << gameHero.hero.getName() << " died." << std::endl;
    }

    if (running) {

      std::string dir;
      is >> dir;

      int xStep = 0;
      int yStep = 0;
      if (dir == "north") { yStep = -1; }
      else if (dir == "south") { yStep = 1; }
      else if (dir == "east") { xStep = 1; }
      else if (dir == "west") { xStep = -1; }
      else if (dir == "exit") { running = false; }

      if (gameMap.get(gameHero.x + xStep, gameHero.y + yStep) == Map::Free) {
        gameHero.y += yStep;
        gameHero.x += xStep;
      }
    }
    else {
      std::cout << gameHero.hero.getName() << ": LVL" << gameHero.hero.getLevel() << std::endl
                << "   HP: "<<gameHero.hero.getHealthPoints()<<"/"<<gameHero.hero.getMaxHealthPoints()<<std::endl
                << "  DMG: "<<gameHero.hero.getDamage().physical<<"/"<<gameHero.hero.getDamage().magical<<std::endl
                << "  ACD: "<<gameHero.hero.getAttackCooldown()<<std::endl
                << "  DEF: "<<gameHero.hero.getDefense()<<std::endl;
    }
  }
}
