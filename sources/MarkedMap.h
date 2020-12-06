#ifndef MARKEDMAP_H
#define MARKEDMAP_H

#include "Map.h"
#include <map>
#include <list>

class MarkedMap : public Map {
  Position heroPosition = Position(-1, -1);
  std::map<char, std::list<Position>> monsterPositions;

public:
  MarkedMap(const std::string& filename);

  Position getHeroPosition() const { return heroPosition; }
  std::list<Position> getMonsterPositions(const char& c) const { return monsterPositions.at(c); }
  std::list<char> getMonsterIDs() const;
};

#endif
