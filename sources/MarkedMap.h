#ifndef MARKEDMAP_H
#define MARKEDMAP_H

#include "Map.h"
#include <map>
#include <list>

/**
 * \class MarkedMap
 * \brief Class for advanced maps, derived from Map.
 *
 * This is a class represents a map, and its layout.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/06 16:43
 */
class MarkedMap : public Map {
  Position heroPosition = Position(-1, -1);
  std::map<char, std::list<Position>> monsterPositions;

public:

  /**
   * \brief Loading constructor.
   * \param filename the name of the map file to be loaded
   * \exception Map::InvalidFileException is thrown on invalid file format
   * \exception Map::FileNotFoundException is thrown when the parameter file does not exist or cannot be opened
   *
   * This function loads a specific map and layout file to the object.
   */
  explicit MarkedMap(const std::string& filename);

  /// Returns the position of the hero that is loaded from the map layout file.
  Position getHeroPosition() const { return heroPosition; }

  /**
   * \brief Getter for monsters.
   * \param c the character that represents the type group of the monster
   * \exception Map::WrongIndexException is thrown on invalid type group specifier
   *
   * This function returns the list of monsters that are specified in the layout with the given paramter.
   */
  std::list<Position> getMonsterPositions(const char& c) const;

  /// Getter that returns a list of the existing monster groups.
  std::list<char> getMonsterIDs() const;
};

#endif
