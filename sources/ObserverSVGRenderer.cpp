#include "ObserverSVGRenderer.h"

#include <fstream>

void ObserverSVGRenderer::render(const Game& game) const {
  Map gameMap = game.getMap();
  Game::GameHero gameHero = game.getHero();
  std::vector<Game::GameMonster> gameMonsters = game.getMonsters();

  std::ofstream file(filename);

  int width = gameMap.getWidth();
  int height = gameMap.getHeight();

  file  << "<svg width=\"" << width * 10 << "\" height=\"" << height * 10
        << "\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n";

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
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
        file << "<g transform=\"translate(" << x * 10 << "," << y * 10 << ")\">";
        std::string textureLine = "";
        while(getline(textureFile, textureLine)) {
          file << "\n\t\t" << textureLine;
        }
        file << "\n\t</g>";

      }
      else {
        file  << "<rect x=\"" << x * 10 << "\" y=\"" << y * 10
              << "\" width=\"10\" height=\"10\" style=\"fill:rgb(0,0,0)\"/>";
      }

      file << "\n";
    }
  }

  file << "</svg>\n";

  file.close();
}
