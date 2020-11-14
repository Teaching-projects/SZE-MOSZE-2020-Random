#ifndef JSON_H
#define JSON_H

#include <string>
#include <map>
#include <variant>
#include <fstream>

#include <iostream>

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


  class List {
    struct Node {
      explicit Node(const std::variant<std::string, float, int>& data) : data(data), prev(nullptr), next(nullptr) {}
      ~Node() {}

      std::variant<std::string, float, int> data;
      Node* prev = nullptr;
      Node* next = nullptr;
    };

    Node* front = nullptr;
    Node* back = nullptr;

    unsigned nodes = 0;

  public:
    List(const List& other);
    List() : front(nullptr), back(nullptr), nodes(0) {}
    ~List() { clear(); }

    List& operator=(const List& other);

    void pushBack(const std::variant<std::string, float, int>& data);
    bool popBack();
    void clear();
    const unsigned& size() const { return nodes; }

    class Iterator {
      Node* act;
    public:
      explicit Iterator(Node* const act) : act(act) {}
      bool operator!=(const Iterator& other) const;
      const Iterator& operator++();
      const std::variant<std::string, float, int>& operator*() const;
    };

    Iterator begin() const;
    Iterator end() const;
  };

private:

  std::map<std::string, std::string> stringMap;  ///< An std::map that stores the loaded string values.
  std::map<std::string, float> floatMap;         ///< An std::map that stores the loaded float values.
  std::map<std::string, int> intMap;             ///< An std::map that stores the loaded int values.
  std::map<std::string, List> listMap;

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
   * \brief Append the maps.
   * \param tag the tag of the to be added value
   * \param value the value that belongs to the tag
   * \exception JSON::ParseException is thrown on unknown value type
   *
   * Appends the class maps with the specified tag value pair.
   */
  template<typename T>
  void append(const std::string& tag, const T& value);

  /**
   * \brief Check for existing tag.
   * \param tag the tag to look for
   * \return unsigned
   *
   * Checks for a tag and returns 0 if not and 1 if the tag is existing.
   */
  unsigned count(const std::string& tag) const;

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
   * \param tag the tag of the JSON value
   * \tparam T describes the type to get
   * \arg int
   * \arg std::string
   * \arg float
   * \return T specified type
   * \exception JSON::ParseException is thrown if the specified tag value is not found
   *
   * Gets the specified type defined by the function call from the JSON object maps and returns its value.
   */
  template<typename T>
  T get(const std::string& tag) const;
};

#endif
