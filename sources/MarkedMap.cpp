#include "MarkedMap.h"
#include <fstream>

MarkedMap::MarkedMap(const std::string& filename) {
  std::ifstream file(filename);

  if (file.is_open()) {
    std::string line;

    while(getline(file, line)) {
      std::vector<type> lineVector;

      if (line.size() > 0) {
        if ((int)line.size() > width) { width = (int)line.size(); }

        for (unsigned i = 0; i < line.size(); ++i) {

          if (line[i] == '#') { lineVector.push_back(Wall); }
          else if (line[i] == ' ') { lineVector.push_back(Free); }
          else if (line[i] == 'H') {
            lineVector.push_back(Free);
            heroPosition = Position(i, height);
          }
          else {
            lineVector.push_back(Free);
            if (monsterPositions.count(line[i])) {
              monsterPositions[line[i]].push_back(Position(i, height));
            }
            else {
              monsterPositions[line[i]] = std::list<Position>(1, Position(i, height));
            }
          }
        }
        mapData.push_back(lineVector);
        ++height;
      }
    }
    if ((heroPosition.x < 0) || (heroPosition.y < 0)) {
      throw InvalidFileException();
    }
  }
  else { throw FileNotFoundException(); }
}

std::list<char> MarkedMap::getMonsterIDs() const {
  std::list<char> ret;
  for (const auto& mp : monsterPositions) {
    ret.push_back(mp.first);
  }
  return ret;
}
