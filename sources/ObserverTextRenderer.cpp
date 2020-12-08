#include "ObserverTextRenderer.h"

void ObserverTextRenderer::render(const Game& game) const {
  Map gameMap = game.getMap();
  Game::GameHero gameHero = game.getHero();
  std::vector<Game::GameMonster> gameMonsters = game.getMonsters();

  int width = gameMap.getWidth();
  int height = gameMap.getHeight();

  std::string text = "╔";
  for (int i = 0; i < width * 2; ++i) { text += "═"; }
  text += "╗\n";

  for (int y = 0; y < height; ++y) {
    text += "║";

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
    text += "║\n";
  }

  text += "╚";
  for (int i = 0; i < width * 2; ++i) { text += "═"; }
  text += "╝";

  *outputStream << text << std::endl;
}
