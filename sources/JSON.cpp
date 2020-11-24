#include "JSON.h"
#include <list>
#include <algorithm>
#include <sstream>

bool isString(const std::string& str) {
  if ((str.back() == '\"') && (str.front() == '\"')) {
    return true;
  }
  return false;
}

bool isFloat(const std::string& str) {
  bool ok = true;
  bool decimal = false;
  for (unsigned i = 0; (i < str.size()) && ok; ++i) {
    if (str[i] == '.') { decimal = true; }

    if ((i == 0) && (str[i] != '-') && (str[i] != '.') && !std::isdigit(str[i])) { ok = false; }
    else if ((i > 0) && !std::isdigit(str[i]) && (str[i] != '.')) { ok = false; }
  }
  return ok && decimal;
}

bool isInt(const std::string& str) {
  bool ok = true;
  for (unsigned i = 0; (i < str.size()) && ok; ++i) {
    if ((i == 0) && (str[i] != '-') && !std::isdigit(str[i])) { ok = false; }
    else if ((i > 0) && !std::isdigit(str[i])) { ok = false; }
  }
  return ok;
}

void strip(std::string& str, const std::string& strip) {
  str.erase(0, str.find_first_not_of(strip));
  str.erase(str.find_last_not_of(strip) + 1);
}

template<>
void JSON::append<std::string>(const std::string& tag, const std::string& value) {
  if (count(tag)) {
    throw ParseException("Tag \"" + tag + "\" already exists!");
  }
  stringMap[tag] = value;
}

template<>
void JSON::append<float>(const std::string& tag, const float& value) {
  if (count(tag)) {
    throw ParseException("Tag \"" + tag + "\" already exists!");
  }
  floatMap[tag] = value;
}

template<>
void JSON::append<int>(const std::string& tag, const int& value) {
  if (count(tag)) {
    throw ParseException("Tag \"" + tag + "\" already exists!");
  }
  intMap[tag] = value;
}

template<>
void JSON::append<JSON::List>(const std::string& tag, const JSON::List& value) {
  if (count(tag)) {
    throw ParseException("Tag \"" + tag + "\" already exists!");
  }
  listMap[tag] = JSON::List(value);
}

unsigned JSON::count(const std::string& tag) const {
  return stringMap.count(tag) + floatMap.count(tag) + intMap.count(tag) + listMap.count(tag);
}

void JSON::parseRaw(std::string data) {
  std::string ws = " \t\n\v\f\r";
  strip(data, ws);

  if (data[0] != '{') { throw ParseException("Missing \"{\" bracket!"); }
  if (data[data.size() - 1] != '}') { throw ParseException("Missing \"}\" bracket!"); }

  data.erase(0, 1);

  if (data.size() == 0) { throw ParseException("Empty JSON file!"); }

  std::string tag = "";
  std::string value = "";

  bool isTag = true;
  bool inQuotes = false;
  bool inList = false;
  JSON::List current_list;
  for (unsigned i = 0; i < data.size(); ++i) {
    if (data[i] == '"') { inQuotes = !inQuotes; }

    if (!inQuotes) {
      if (data[i] == ':') { isTag = false; }
      else if (data[i] == '[') { inList = true; }
      else if (data[i] == ',' || data[i] == '}' || data[i] == ']') {
        strip(value, ws);

        if (inList) {
          if (value.size() == 0) { throw ParseException("Invalid value!"); }

          if (data[i] == '}') { throw ParseException("Invalid end of file!"); }
          if (data[i] == ']') { inList = false; }


          if (isString(value)) {
            value = value.substr(1, value.size() - 2);
            current_list.pushBack(value);
          }
          else if (isFloat(value)) {
            current_list.pushBack(std::stof(value));
          }
          else if (isInt(value)) {
            current_list.pushBack(std::stoi(value));
          }
          else { throw ParseException("Unknown value type! \"" + value + "\""); }

          value = "";
        }
        else {
          if ((value.size() == 0) && (current_list.size() == 0)) { throw ParseException("Invalid value!"); }

          if (data[i] == ']') { throw ParseException("Invalid end of list!"); }

          strip(tag, ws);
          if (isString(tag)) {
            tag = tag.substr(1, tag.size() - 2);
          }
          else {
            for (const auto& t : tag) {
              if (isspace(t)) {
                throw ParseException("Invalid tag!");
              }
            }
          }
          if (tag.size() == 0) { throw ParseException("Invalid tag!"); }

          if (count(tag)) {
            throw ParseException("Multiple definition of \"" + tag + "\"!");
          }

          if (current_list.size() > 0) { append<JSON::List>(tag, current_list); }
          else if (isString(value)) { append<std::string>(tag, value.substr(1, value.size() - 2)); }
          else if (isFloat(value)) { append<float>(tag, std::stof(value)); }
          else if (isInt(value)) { append<int>(tag, std::stoi(value)); }
          else { throw ParseException("Unknown value type! \"" + value + "\""); }

          isTag = true;
          tag = "";
          value = "";
          current_list.clear();
        }
      }
      else {
        if (isTag) { tag += data[i]; }
        else { value += data[i]; }
      }
    }
    else {
      if (isTag) { tag += data[i]; }
      else { value += data[i]; }
    }
  }
  if (!isTag || inQuotes) { throw ParseException("Invalid end of file!"); }
}

JSON JSON::parseFromFile(const std::string& filename) {
  JSON ret;
  std::ifstream file(filename);

  if (file.is_open()) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    ret.parseRaw(buffer.str());

    file.close();
  }
  else {
    throw ParseException("Failed to open file!");
  }
  return ret;
}

JSON JSON::parseFromStream(std::ifstream& file) {
  JSON ret;

  if (file.is_open()) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    ret.parseRaw(buffer.str());

    file.close();
  }
  else {
    throw ParseException("Invalid stream!");
  }
  return ret;
}

JSON JSON::parseFromString(const std::string& text) {
  if (text.size() == 0) { throw ParseException("Input string is empty!"); }
  JSON ret;
  ret.parseRaw(text);
  return ret;
}

template<>
std::string JSON::get<std::string>(const std::string& tag) const {
  try {
    return stringMap.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw ParseException("Tag \"" + tag + "\" not found!");
  }
}

template<>
float JSON::get<float>(const std::string& tag) const {
  try {
    return floatMap.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw ParseException("Tag \"" + tag + "\" not found!");
  }
}

template<>
int JSON::get<int>(const std::string& tag) const {
  try {
    return intMap.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw ParseException("Tag \"" + tag + "\" not found!");
  }
}

template<>
JSON::List JSON::get<JSON::List>(const std::string& tag) const {
  try {
    return listMap.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw ParseException("Tag \"" + tag + "\" not found!");
  }
}
