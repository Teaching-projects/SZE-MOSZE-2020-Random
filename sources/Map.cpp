#include "Map.h"

#include <iostream>
#include <fstream>

Map::Map(const std::string& filename) {
  std::ifstream file(filename);

  if (file.is_open()) {
    std::string line;

    while(getline(file, line)) {
      std::vector<type> lineVector;

      if (line.size() > 0) {
        ++height;
        if ((int)line.size() > width) { width = (int)line.size(); }

        for (unsigned i = 0; i < line.size(); ++i) {

          if (line[i] == '#') { lineVector.push_back(Wall); }
          else if (line[i] == ' ') { lineVector.push_back(Free); }
          else { std::cerr << "throw another error" << std::endl; }
        }
        mapData.push_back(lineVector);
      }
    }
  }
  else {
    std::cerr << "throw error" << std::endl;
  }
}

Map::type Map::get(const int& x, const int& y) const {
  return Wall;
}
