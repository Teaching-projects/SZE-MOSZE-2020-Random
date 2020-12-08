#include "HeroTextRenderer.h"

void HeroTextRenderer::render(const Game& game) const {
  Map gameMap = game.getMap();
  Game::GameHero gameHero = game.getHero();
  std::vector<Game::GameMonster> gameMonsters = game.getMonsters();

  int radius = (int)gameHero.hero.getLightRadius();

  int xStart = gameHero.x - radius;
  int xEnd = gameHero.x + radius;
  int yStart = gameHero.y - radius;
  int yEnd = gameHero.y + radius;

  int width = gameMap.getWidth();
  int height = gameMap.getHeight();

  if (xStart < 0) { xStart = 0; }
  if (xEnd >= width) { xEnd = width - 1; }

  if (yStart < 0) { yStart = 0; }
  if (yEnd >= height) { yEnd = height - 1; }

  std::string text = "╔";
  for (int i = 0; i < ((xEnd + 1) - xStart) * 2; ++i) { text += "═"; }
  text += "╗\n";

  for (int y = yStart; y <= yEnd; ++y) {
    text += "║";

    for (int x = xStart; x <= xEnd; ++x) {

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
  for (int i = 0; i < ((xEnd + 1) - xStart) * 2; ++i) { text += "═"; }
  text += "╝";

  *outputStream << text << std::endl;
}
