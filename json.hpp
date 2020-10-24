#ifndef JSON_H
#define JSON_H

#include <string>
#include <map>
#include <fstream>

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
class JsonException : public std::exception {
  std::string s;
public:
  JsonException(const std::string& ss) : s(ss) {}
  ~JsonException() throw() {}
  const char* what() const throw() { return s.c_str(); }
};

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
class Json {
  std::map<std::string, std::string> string_map;  ///< An std::map that stores the loaded string values.
  std::map<std::string, float> float_map;         ///< An std::map that stores the loaded float values.
  std::map<std::string, int> int_map;             ///< An std::map that stores the loaded int values.

  /**
   * \brief Function for loading raw data.
   * \param data a string that stores the raw cleared JSON data
   * \exception JsonException is thrown on syntax errors
   *
   * This function loads cleaned JSON strings to the maps.
   */
  void parse_raw(const std::string& data);

public:

  /**
   * \brief Parsing via filename.
   * \param filename the name of the file to be parsed from
   * \exception JsonException is thrown on reading, syntax errors
   *
   * Opens the file specified by the filename parameter and reads the JSON values.
   */
  void parse_file(const std::string& filename);

  /**
   * \brief Parsing via std::ifstream.
   * \param file the std::ifstream of the file to be parsed from
   * \exception JsonException is thrown on unopened file and syntax errors
   *
   * Reads from the std::ifstream specified by the file parameter.
   */
  void parse_stream(std::ifstream& file);

  /**
   * \brief Parsing via string.
   * \param file contains the formatted string data of a JSON file
   * \exception JsonException is thrown on empty string and syntax errors
   *
   * Reads from string given as the text parameter.
   */
  void parse_string(const std::string& text);

  /**
   * \brief Gets a loaded string value.
   * \param tag the gat of the value
   * \exception JsonException is thrown on reading failure
   */
  std::string get_string(const std::string& tag) const;

  /**
   * \brief Gets a loaded float value.
   * \param tag the gat of the value
   * \exception JsonException is thrown on reading failure
   */
  float get_float(const std::string& tag) const;

  /**
   * \brief Gets a loaded int value.
   * \param tag the gat of the value
   * \exception JsonException is thrown on reading failure
   */
  int get_int(const std::string& tag) const;
};

#endif
