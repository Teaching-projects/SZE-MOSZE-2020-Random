#include "JSON.h"
#include <list>
#include <algorithm>
#include <iostream>
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

void JSON::append(const std::string& key, const std::string& value) {
  if (stringMap.count(key) || floatMap.count(key) || intMap.count(key)) {
    throw ParseException("Key \"" + key + "\" already exists!");
  }
  if (isString(value)) {
    stringMap[key] = (std::string)value.substr(1, value.size() - 2);
  }
  else if (isFloat(value)) {
    floatMap[key] = (float)std::stof(value);
  }
  else if (isInt(value)) {
    intMap[key] = (int)std::stoi(value);
  }
  else {
    throw ParseException("Unknown value type! \"" + value + "\"");
  }
}

unsigned JSON::count(const std::string& key) const {
  return stringMap.count(key) + floatMap.count(key) + intMap.count(key);
}

void JSON::parseRaw(std::string data) {
  std::string ws = " \t\n\v\f\r";
  data.erase(0, data.find_first_not_of(ws));
  data.erase(data.find_last_not_of(ws) + 1);

  if (data[0] != '{') { throw ParseException("Missing \"{\" bracket!"); }
  if (data[data.size() - 1] != '}') { throw ParseException("Missing \"}\" bracket!"); }

  data.erase(0, 1);

  if (data.size() == 0) { throw ParseException("Empty JSON file!"); }

  std::string tag = "";
  std::string value = "";

  bool isTag = true;
  bool inQuotes = false;
  for (unsigned i = 0; i < data.size(); ++i) {
    if (data[i] == '"') { inQuotes = !inQuotes; }
    if (inQuotes) {
      if (isTag) { tag += data[i]; }
      else { value += data[i]; }
    }
    else {
      if (data[i] == ':') { isTag = false; }
      else if (data[i] == ',' || data[i] == '}') {
        tag = tag.substr(1, tag.size() - 2);

        if (tag.size() <= 0) { throw ParseException("Invalid tag!"); }

        if (value.size() <= 0) { throw ParseException("Invalid value!"); }

        if (stringMap.count(key) || floatMap.count(key) || intMap.count(key)) {
          throw ParseException("Multiple definition of \"" + tag + "\"!");
        }

        append(tag, value);

        isTag = true;
        tag = "";
        value = "";
      }
      else if (!isspace(data[i])) {
        if (isTag) { tag += data[i]; }
        else { value += data[i]; }
      }
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
  if (text.size() <= 0) { throw ParseException("Input string is empty!"); }
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
