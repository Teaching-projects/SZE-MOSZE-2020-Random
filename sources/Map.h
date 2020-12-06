#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

struct Position {
  int x = 0;
  int y = 0;

  Position() {}
  Position(const int& x, const int& y) : x(x), y(y) {}
};

/**
 * \class Map
 * \brief Class for loading and using maps.
 *
 * This is a class that represents a map, that is used by the game.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/12/02 14:04
 */
class Map {
public:
  enum type { Wall, Free }; ///< Types for identifying the map positions.

  /**
   * \class Map::WrongIndexException
   *
   * This is an exception class used by the Map class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/01 15:25
   */
  class WrongIndexException : public std::exception {
  public:
    ~WrongIndexException() throw() {}
    const char* what() const throw() { return "Wrong index."; }
  };

  /**
   * \class Map::InvalidFileException
   *
   * This is an exception class used by the Map class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/01 15:25
   */
  class InvalidFileException : public std::exception {
  public:
    ~InvalidFileException() throw() {}
    const char* what() const throw() { return "Invalid file."; }
  };

  /**
   * \class Map::FileNotFoundException
   *
   * This is an exception class used by the Map class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/12/01 15:25
   */
  class FileNotFoundException : public std::exception {
  public:
    ~FileNotFoundException() throw() {}
    const char* what() const throw() { return "Requested file not found."; }
  };

protected:
  int width = 0;                            ///< The width of the map.
  int height = 0;                           ///< The height of the map.
  std::vector<std::vector<type>> mapData;   ///< Map values stored in a std::vector.

public:
  /// Default constructor, creates an empty Map.
  Map() {}

  /**
   * \brief Loading constructor.
   * \param filename the name of the map file to be loaded
   * \exception Map::InvalidFileException is thrown on invalid file format
   * \exception Map::FileNotFoundException is thrown when the parameter file does not exist or cannot be opened
   *
   * This function loads a specific map file to the object.
   */
  explicit Map(const std::string& filename);

  /**
   * \brief Position getter.
   * \param x the x coordinate of the point to be read
   * \param y the y coordinate of the point to be read
   * \exception Map::WrongIndexException is thrown when the given index is not valid
   * \return type
   *
   * This function returns the value of the position given as parameters.
   */
  type get(const int& x, const int& y) const;

  type get(const Position& pos) const { return get(pos.x, pos.y); }

  /// Getter for the width of the map.
  int getWidth() const { return width; }

  /// Getter for the height of the map.
  int getHeight() const { return height; }
};

#endif
