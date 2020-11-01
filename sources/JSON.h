#ifndef JSON_H
#define JSON_H

#include <string>
#include <map>
#include <fstream>

/**
 * \class Json
 * \brief Class for JSON files.
 *
 * Parses a JSON file from different sources, and uses functions to read its values.
 *
 * \author LengyHELL
 * \version 1.0
 * \date 2020/10/20 21:36
 */
class JSON {
  std::map<std::string, std::string> stringMap;  ///< An std::map that stores the loaded string values.
  std::map<std::string, float> floatMap;         ///< An std::map that stores the loaded float values.
  std::map<std::string, int> intMap;             ///< An std::map that stores the loaded int values.

  /**
   * \brief Function for loading raw data.
   * \param data a string that stores the raw cleared JSON data
   * \exception JsonException is thrown on syntax errors
   *
   * This function loads cleaned JSON strings to the maps.
   */
  void parseRaw(std::string data);

public:
  /**
   * \class JsonException
   * \brief An exception class.
   *
   * This is an exception class used by the Json class.
   *
   * \author LengyHELL
   * \version 1.0
   * \date 2020/10/20 21:36
   */
  class ParseException : public std::exception {
    std::string s;
  public:
    ParseException(const std::string& ss) : s(ss) {}
    ~ParseException() throw() {}
    const char* what() const throw() { return s.c_str(); }
  };

  void append(const std::string& key, const std::string& value);

  unsigned count(const std::string& key) const;

  /**
   * \brief Parsing via filename.
   * \param filename the name of the file to be parsed from
   * \exception JsonException is thrown on reading, syntax errors
   *
   * Opens the file specified by the filename parameter and reads the JSON values.
   */
  static JSON parseFromFile(const std::string& filename);

  /**
   * \brief Parsing via std::ifstream.
   * \param file the std::ifstream of the file to be parsed from
   * \exception JsonException is thrown on unopened file and syntax errors
   *
   * Reads from the std::ifstream specified by the file parameter.
   */
  static JSON parseFromStream(std::ifstream& file);

  /**
   * \brief Parsing via string.
   * \param file contains the formatted string data of a JSON file
   * \exception JsonException is thrown on empty string and syntax errors
   *
   * Reads from string given as the text parameter.
   */
  static JSON parseFromString(const std::string& text);

  template<typename T>
  T get(const std::string& tag) const;
};

#endif
