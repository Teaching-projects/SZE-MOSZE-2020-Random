#include "JSON.h"
#include <list>
#include <algorithm>
#include <iostream>

bool is_string(const std::string& str) {
  if ((str.back() == '\"') && (str.front() == '\"')) {
    return true;
  }
  return false;
}

bool is_float(const std::string& str) {
  bool ok = true;
  bool decimal = false;
  for (unsigned i = 0; (i < str.size()) && ok; ++i) {
    if (str[i] == '.') { decimal = true; }

    if ((i == 0) && (str[i] != '-') && (str[i] != '.') && !std::isdigit(str[i])) { ok = false; }
    else if ((i > 0) && !std::isdigit(str[i]) && (str[i] != '.')) { ok = false; }
  }
  return ok && decimal;
}

bool is_int(const std::string& str) {
  bool ok = true;
  for (unsigned i = 0; (i < str.size()) && ok; ++i) {
    if ((i == 0) && (str[i] != '-') && !std::isdigit(str[i])) { ok = false; }
    else if ((i > 0) && !std::isdigit(str[i])) { ok = false; }
  }
  return ok;
}

void JSON::append(const std::string& key, const std::string& value) {
  if (is_string(value)) {
    string_map[key] = (std::string)value.substr(1, value.size() - 2);
  }
  else if (is_float(value)) {
    float_map[key] = (float)std::stof(value);
  }
  else if (is_int(value)) {
    int_map[key] = (int)std::stoi(value);
  }
  else {
    throw ParseException("Unknown value type! \"" + value + "\"");
  }
}

JSON JSON::parse_raw(std::string data) {
  JSON ret;

  std::string ws = " \t\n\v\f\r";
  data.erase(0, data.find_first_not_of(ws));
  data.erase(data.find_last_not_of(ws) + 1);

  if (data[0] != '{') { throw ParseException("Missing \"{\" bracket!"); }
  if (data[data.size() - 1] != '}') { throw ParseException("Missing \"}\" bracket!"); }

  data.erase(0, 1);

  if (data.size() == 0) { throw ParseException("Empty JSON file!"); }

  std::string tag = "";
  std::string value = "";

  std::list<std::string> tags;

  bool is_tag = true;
  bool in_quotes = false;
  for (unsigned i = 0; i < data.size(); ++i) {
    if (data[i] == '"') { in_quotes = !in_quotes; }
    if (in_quotes) {
      if (is_tag) { tag += data[i]; }
      else { value += data[i]; }
    }
    else {
      if (data[i] == ':') { is_tag = false; }
      else if (data[i] == ',' || data[i] == '}') {
        tag = tag.substr(1, tag.size() - 2);

        if (tag.size() <= 0) { throw ParseException("Invalid tag!"); }

        if (value.size() <= 0) { throw ParseException("Invalid value!"); }

        if (std::find(tags.begin(), tags.end(), tag) != tags.end()) {
          throw ParseException("Multiple definition of \"" + tag + "\"!");
        }
        else { tags.push_back(tag); }

        ret.append(tag, value);

        is_tag = true;
        tag = "";
        value = "";
      }
      else if (!isspace(data[i])) {
        if (is_tag) { tag += data[i]; }
        else { value += data[i]; }
      }
    }
  }
  if (!is_tag || in_quotes) { throw ParseException("Invalid end of file!"); }
  return ret;
}

std::string clear_file(std::ifstream& file) {
  std::string data = "";
  if (file.is_open()) {
    char c;
    std::string sep = "{,}";
    bool in_quotes = false;
    while(file.get(c)) {
      if (c == '\"') {
        in_quotes = !in_quotes;
      }
      if (!isspace(c) || in_quotes) { data += c; }
    }
  }
  return data;
}

JSON JSON::parseFromFile(const std::string& filename) {
  JSON ret;
  std::ifstream file(filename);

  if (file.is_open()) {
    std::string raw = clear_file(file);
    ret = parse_raw(raw);

    file.close();
  }
  else {
    throw ParseException("Failed to open file!");
  }
  return ret;
}

void JSON::parse_stream(std::ifstream& file) {
  if (file.is_open()) {
    std::string raw = clear_file(file);
    parse_raw(raw);

    file.close();
  }
  else {
    throw ParseException("Invalid stream!");
  }
}

void JSON::parse_string(const std::string& text) {
  if (text.size() <= 0) { throw ParseException("Parsed string is empty!"); }

  std::string sep = "{,}";
  std::string data = "";
  bool in_quotes = false;
  for (const auto& c : text) {
    if (c == '\"') {
      in_quotes = !in_quotes;
    }
    if (!isspace(c) || in_quotes) { data += c; }
  }

  parse_raw(data);
}

template<>
std::string JSON::get<std::string>(const std::string& tag) const {
  try {
    return string_map.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw ParseException("Tag \"" + tag + "\" not found!");
  }
}

template<>
float JSON::get<float>(const std::string& tag) const {
  try {
    return float_map.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw ParseException("Tag \"" + tag + "\" not found!");
  }
}

template<>
int JSON::get<int>(const std::string& tag) const {
  try {
    return int_map.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw ParseException("Tag \"" + tag + "\" not found!");
  }
}
