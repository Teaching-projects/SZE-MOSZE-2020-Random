#include "PreparedGame.h"
#include "JSON.h"
#include "MarkedMap.h"

PreparedGame::PreparedGame(const std::string& filename) {
  JSON file = JSON::parseFromFile(filename);
  MarkedMap tempMap(file.get<std::string>("map"));

  wallTexture = file.get<std::string>("wall_texture");
  freeTexture = file.get<std::string>("free_texture");

  setMap(tempMap);

  putHero(Hero::parse(file.get<std::string>("hero")), tempMap.getHeroPosition().x, tempMap.getHeroPosition().y);

  for (const auto& mid : tempMap.getMonsterIDs()) {
    for (const auto& p : tempMap.getMonsterPositions(mid)) {
      std::string monsterTag = "monster-";
      monsterTag += mid;
      putMonster(Monster::parse(file.get<std::string>(monsterTag)), p.x, p.y);
    }
  }
}
