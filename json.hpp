#ifndef JSON_H
#define JSON_H

#include <string>
#include <map>
#include <fstream>

class JsonException : public std::exception {
  std::string s;
public:
  JsonException(const std::string& ss) : s(ss) {}
  ~JsonException() throw() {}
  const char* what() const throw() { return s.c_str(); }
};

class Json {
  std::map<std::string, std::string> string_map;
  std::map<std::string, float> float_map;
  std::map<std::string, int> int_map;
  void parse_raw(const std::string& data);

public:
  void parse_file(const std::string& filename);
  void parse_stream(std::ifstream& file);
  void parse_string(const std::string& text);

  std::string get_string(const std::string& tag) const;
  float get_float(const std::string& tag) const;
  int get_int(const std::string& tag) const;
};

#endif
