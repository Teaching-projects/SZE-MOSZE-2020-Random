#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Map {
public:
  enum type { Wall, Free };

private:
  int width = 0;
  int height = 0;
  std::vector<std::vector<type>> mapData;

public:
  Map() {}
  Map(const std::string& filename);

  type get(const int& x, const int& y) const;

  int getWidth() const { return width; }
  int getHeight() const { return height; }
};

#endif
