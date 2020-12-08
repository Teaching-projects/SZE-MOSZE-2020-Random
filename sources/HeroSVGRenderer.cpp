#include "HeroSVGRenderer.h"

#include <fstream>

void HeroSVGRenderer::render(const Game& game) const {
  Map gameMap = game.getMap();
  Game::GameHero gameHero = game.getHero();
  std::vector<Game::GameMonster> gameMonsters = game.getMonsters();

  std::ofstream file(filename);

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

  file  << "<svg width=\"" << ((xEnd + 1) - xStart) * 10 << "\" height=\"" << ((yEnd + 1) - yStart) * 10
        << "\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n";

  for (int y = yStart; y <= yEnd; ++y) {
    for (int x = xStart; x <= xEnd; ++x) {
      file << "\t";
      std::string texture = "";

      if (gameMap.get(x, y) == Map::Free) {
        if ((x == gameHero.x) && (y == gameHero.y)) {
          texture = gameHero.hero.getTexture();
        }
        else {
          int monsterCount = 0;
          for (const auto& m : gameMonsters) {
            if ((x == m.x) && (y == m.y)) {
              texture = m.monster.getTexture();
              ++monsterCount;
            }
            if (monsterCount >= 2) { break; }
          }

          if (monsterCount == 0) {
            texture = game.getFreeTexture();
          }
        }
      }
      else {
        texture = game.getWallTexture();
      }

      std::ifstream textureFile(texture);
      if (textureFile.is_open()) {
        file << "<g transform=\"translate(" << (x - xStart) * 10 << "," << (y - yStart) * 10 << ")\">";
        std::string textureLine = "";
        while(getline(textureFile, textureLine)) {
          file << "\n\t\t" << textureLine;
        }
        file << "\n\t</g>";

      }
      else {
        file  << "<rect x=\"" << (x - xStart) * 10 << "\" y=\"" << (y - yStart) * 10
        << "\" width=\"10\" height=\"10\" style=\"fill:rgb(0,0,0)\"/>";
      }

      file << "\n";
    }
  }

  file << "</svg>\n";

  file.close();
}
