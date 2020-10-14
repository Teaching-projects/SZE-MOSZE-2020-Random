#include "json.hpp"
#include <vector>
#include <algorithm>

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

void Json::parse_raw(const std::string& data) {
  string_map.clear();
  float_map.clear();
  int_map.clear();

  std::vector<std::string> tags;
  std::string sep = "{,}";

  if (data.front() != '{') { throw JsonException("Invalid syntax!"); }

  int begin = data.find_first_of(sep) + 1;
  int end = 0;
  bool close = false;
  while (end < (int)data.size() - 1) {
    if (close) { throw JsonException("Invalid syntax!"); }

    end = data.find_first_of(sep, begin);

    if (end == -1) { throw JsonException("Invalid syntax!"); }

    std::string line = data.substr(begin, end - begin);

    if (data[end] == '}') { close = true; }
    else { begin = end + 1; }

    //processing line
    int count = 0;
    for (unsigned i = 0; i < line.size(); ++i) {
      if (line[i] == ':') { count++; }
    }
    if (count != 1) { throw JsonException("Invalid syntax!"); }

    std::string tag = line.substr(0, line.find(":"));
    std::string value = line.substr(line.find(":") + 1);

    if ((tag.front() != '\"') || (tag.back() != '\"')) { throw JsonException("Invalid syntax!"); }

    tag = tag.substr(1, tag.size() - 2);

    if (tag.size() <= 0) { throw JsonException("Invalid syntax!"); }

    if (value.size() <= 0) { throw JsonException("Invalid syntax!"); }

    if (std::find(tags.begin(), tags.end(), tag) != tags.end()) {
      throw JsonException("Multiple definition of \"" + tag + "\"!");
    }
    else {
      tags.push_back(tag);
    }

    //read tags
    if (is_string(value)) {
      string_map[tag] = (std::string)value.substr(1, value.size() - 2);
    }
    else if (is_float(value)) {
      float_map[tag] = (float)std::stof(value);
    }
    else if (is_int(value)) {
      int_map[tag] = (int)std::stoi(value);
    }
  }
}

void Json::parse_file(const std::string& filename) {
  std::ifstream file(filename);

  if (file.is_open()) {
    char c;
    std::string sep = "{,}";
    std::string data = "";
    bool in_quotes = false;
    while(file.get(c)) {
      if (c == '\"') {
        in_quotes = !in_quotes;
      }
      if (!isspace(c) || in_quotes) { data += c; }
    }

    parse_raw(data);

    file.close();
  }
  else {
    throw JsonException("Failed to open file!");
  }
}

void Json::parse_stream(std::ifstream& file) {
  if (file.is_open()) {
    char c;
    std::string sep = "{,}";
    std::string data = "";
    bool in_quotes = false;
    while(file.get(c)) {
      if (c == '\"') {
        in_quotes = !in_quotes;
      }
      if (!isspace(c) || in_quotes) { data += c; }
    }

    parse_raw(data);

    file.close();
  }
  else {
    throw JsonException("Invalid stream!");
  }
}

void Json::parse_string(const std::string& text) {
  if (text.size() <= 0) { throw JsonException("Parsed string is empty!"); }

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

std::string Json::get_string(const std::string& tag) const {
  try {
    return string_map.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw JsonException("Tag \"" + tag + "\" not found!");
  }
}

float Json::get_float(const std::string& tag) const {
  try {
    return float_map.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw JsonException("Tag \"" + tag + "\" not found!");
  }
}

int Json::get_int(const std::string& tag) const {
  try {
    return int_map.at(tag);
  }
  catch (const std::out_of_range& e) {
    throw JsonException("Tag \"" + tag + "\" not found!");
  }
}
