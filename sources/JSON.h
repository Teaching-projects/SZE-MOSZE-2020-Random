#ifndef JSON_H
#define JSON_H

#include <string>
#include <map>
#include <fstream>

/**
 * \class JSON
 * \brief Class for JSON files.
 *
 * Parses a JSON file from different sources, and uses functions to read its values.
 *
 * \author LengyHELL
 * \version 1.1
 * \date 2020/11/01 17:36
 */
class JSON {
  std::map<std::string, std::string> stringMap;  ///< An std::map that stores the loaded string values.
  std::map<std::string, float> floatMap;         ///< An std::map that stores the loaded float values.
  std::map<std::string, int> intMap;             ///< An std::map that stores the loaded int values.

  /**
   * \brief Function for loading raw data.
   * \param data an std::string that stores the raw JSON data
   * \exception JSON::ParseException is thrown on syntax errors
   *
   * This function loads a JSON string values to the corresponding maps.
   */
  void parseRaw(std::string data);

public:
  /**
   * \class JSON::ParseException
   * \brief An exception class.
   *
   * This is an exception class used by the JSON class. Derives from the std::exception class.
   *
   * \author LengyHELL
   * \version 1.1
   * \date 2020/11/01 17:41
   */
  class ParseException : public std::exception {
    std::string s;
  public:
    explicit ParseException(const std::string& ss) : s(ss) {}
    ~ParseException() throw() {}
    const char* what() const throw() { return s.c_str(); }
  };

  /**
   * \brief Append the maps.
   * \param key the key of the to be added value
   * \param value the value that belongs to the key
   * \exception JSON::ParseException is thrown on unknown value type
   *
   * Appends the class maps with the specified key value pair.
   */
  void append(const std::string& key, const std::string& value);

  /**
   * \brief Check for existing key.
   * \param key the key to look for
   * \return unsigned
   *
   * Checks for a key and returns 0 if not and 1 if the key is existing.
   */
  unsigned count(const std::string& key) const;

  /**
   * \brief Parsing via filename.
   * \param filename the name of the file to be parsed from
   * \exception JSON::ParseException is thrown on reading, syntax errors
   * \return JSON object
   *
   * Opens the file specified by the filename parameter and reads the JSON values, that are returned as a JSON object.
   */
  static JSON parseFromFile(const std::string& filename);

  /**
   * \brief Parsing via std::ifstream.
   * \param file the std::ifstream of the file to be parsed from
   * \exception JSON::ParseException is thrown on unopened file and syntax errors
   * \return JSON object
   *
   * Reads from the std::ifstream specified by the file parameter, and returns the values as a JSON object.
   */
  static JSON parseFromStream(std::ifstream& file);

  /**
   * \brief Parsing via string.
   * \param file contains the formatted string data of a JSON file
   * \exception JSON::ParseException is thrown on empty string and syntax errors
   * \return JSON object
   *
   * Reads from std::string given as the text parameter, returns the values as a JSON object.
   */
  static JSON parseFromString(const std::string& text);

  /**
   * \brief Geting value.
   * \param tag the key of the JSON value
   * \tparam T describes the type to get
   * \arg int
   * \arg std::string
   * \arg float
   * \return T specified type
   * \exception JSON::ParseException is thrown if the specified key value is not found
   *
   * Gets the specified type defined by the function call from the JSON object maps and returns its value.
   */
  template<typename T>
  T get(const std::string& tag) const;
};

#endif
