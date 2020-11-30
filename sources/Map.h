#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Map {
public:
  enum type { Wall, Free };

  class WrongIndexException : public std::exception {
  public:
    ~WrongIndexException() throw() {}
    const char* what() const throw() { return "Wrong index."; }
  };

  class InvalidFileException : public std::exception {
  public:
    ~InvalidFileException() throw() {}
    const char* what() const throw() { return "Invalid file."; }
  };

  class FileNotFoundException : public std::exception {
  public:
    ~FileNotFoundException() throw() {}
    const char* what() const throw() { return "Requested file not found."; }
  };

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
